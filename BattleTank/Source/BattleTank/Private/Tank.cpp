// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "StaticLibrary.h"

// Sets default values
ATank::ATank() {
	PrimaryActorTick.bCanEverTick = false;
	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::BeginPlay() {
	Super::BeginPlay();
	//TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
}


