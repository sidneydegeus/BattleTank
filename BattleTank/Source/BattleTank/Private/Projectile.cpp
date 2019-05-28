// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "StaticLibrary.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Classes/Particles/ParticleSystemComponent.h"

//needed to remove intellisense errors. Compiles without as well.
#include "Classes/Components/StaticMeshComponent.h"

// Sets default values
AProjectile::AProjectile(){
	PrimaryActorTick.bCanEverTick = true;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false;
}

void AProjectile::BeginPlay(){
	Super::BeginPlay();	
}


void AProjectile::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

void AProjectile::LaunchProjectile(float Speed) {
	//UStaticLibrary::PrintWarning(FString("Firing!!"), FString(__FILE__), __LINE__);
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovement->Activate();
}

