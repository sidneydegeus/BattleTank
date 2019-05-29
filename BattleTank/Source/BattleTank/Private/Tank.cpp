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

float ATank::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) {
	int32 DamagePoints = FPlatformMath::RoundToInt(Damage);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);
	
	CurrentHealth -= DamageToApply;

	return DamageToApply;
}

float ATank::GetHealthPercentage() const {
	return (float)CurrentHealth / (float)MaxHealth;
}

