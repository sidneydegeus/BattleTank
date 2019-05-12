// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "StaticLibrary.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile(){
	PrimaryActorTick.bCanEverTick = true;
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

