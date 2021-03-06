// Fill out your copyright notice in the Description page of Project Settings.


#include "SprungWheel.h"

#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SphereComponent.h"

#include "Net/UnrealNetwork.h"

void ASprungWheel::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASprungWheel, ReplicatedLocation);
}

// Sets default values
ASprungWheel::ASprungWheel() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassWheelConstraint"));
	SetRootComponent(MassWheelConstraint);

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetupAttachment(MassWheelConstraint);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axle);

	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelConstraint"));
	AxleWheelConstraint->SetupAttachment(Axle);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay() {
	Super::BeginPlay();

	//
	//AActor* Owner = GetOwner();
	//if (Owner != nullptr) {
	//	UE_LOG(LogTemp, Warning, TEXT("Owner %s"), *Owner->GetName());
	//	//Wheel->MoveIgnoreActors.Add(Owner);
	//	Wheel->IgnoreActorWhenMoving(Owner, true);
	//	Wheel->
	//	Wheel->IgnoreComponentWhenMoving(Owner->GetComponents);
	//	//Axle->MoveIgnoreActors.Add(Owner);
	//	Axle->IgnoreActorWhenMoving(Owner, true);
	//}
	//else {
	//	UE_LOG(LogTemp, Warning, TEXT("no owner"));
	//}

	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);

	SetupConstraint();
}

void ASprungWheel::SetupConstraint() {
	if (!GetAttachParentActor()) return;
	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) return;
	MassWheelConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);
	AxleWheelConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (GetWorld()->TickGroup == TG_PostPhysics) {
		TotalForceMagnitudeThisFrame = 0;
	}

	//if (HasAuthority()) {
	//	ReplicatedLocation = GetActorLocation();
	//}
	//else {
	//	SetActorLocation(ReplicatedLocation);
	//}
}

void ASprungWheel::AddDrivingForce(float ForceMagnitude) {
	TotalForceMagnitudeThisFrame += ForceMagnitude;
}

// TODO: maybe disable? idk
void ASprungWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Black, FString::Printf(TEXT("Bool: %s"), HasAuthority() ? TEXT("true") : TEXT("false")));
	if (TotalForceMagnitudeThisFrame == 0) {
		Wheel->SetAngularDamping(500);
	}
	else {
		Wheel->SetAngularDamping(0);
		ApplyForce();
	}
}

void ASprungWheel::ApplyForce() {
	Wheel->AddForce(Axle->GetForwardVector() * TotalForceMagnitudeThisFrame);
}

