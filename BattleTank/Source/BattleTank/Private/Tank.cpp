// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "StaticLibrary.h"
#include "TankBarrel.h"

// Sets default values
ATank::ATank() {
	PrimaryActorTick.bCanEverTick = false;
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet) {
	TankAimingComponent->SetBarrelReference(BarrelToSet);
}

void ATank::SetTurretReference(UTankTurret* TurretToSet) {
	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::BeginPlay(){
	Super::BeginPlay();	
}


void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::AimAt(FVector HitLocation) {
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire() {
	UStaticLibrary::PrintWarning(FString("Firing!!"), FString(__FILE__), __LINE__);
}

