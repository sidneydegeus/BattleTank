// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "StaticLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

#pragma region PUBLIC
void UTankAimingComponent::Initialize(UTankBarrel* TankBarrelToSet, UTankTurret* TankTurretToSet) {
	Barrel = TankBarrelToSet;
	Turret = TankTurretToSet;
}

void UTankAimingComponent::Fire() {
	if (!ensure(Barrel && ProjectileBlueprint)) return;

	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (isReloaded) {
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

void UTankAimingComponent::AimAt(FVector HitLocation) {
	if (!ensure(Barrel)) {
		UStaticLibrary::PrintWarning(FString("No Barrel Found"), FString(__FILE__), __LINE__);
		return;
	}

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
		//FCollisionResponseParams::DefaultResponseParam,
		//TArray<AActor*>(),
		//true //debug draw
	);


	if (bHaveAimSolution) {
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}
#pragma endregion PUBLIC

#pragma region PRIVATE
UTankAimingComponent::UTankAimingComponent() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	if (!ensure(Barrel || Turret)) return;

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}

#pragma endregion PRIVATE

