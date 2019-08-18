// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "StaticLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

#include "Net/UnrealNetwork.h"

#pragma region PUBLIC
void UTankAimingComponent::Initialize(UTankBarrel* TankBarrelToSet, UTankTurret* TankTurretToSet) {
	Barrel = TankBarrelToSet;
	Turret = TankTurretToSet;
}

void UTankAimingComponent::Fire() {
	if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming) {
		Server_Fire();
		FiringState = EFiringState::Reloading;
	}
}

void UTankAimingComponent::Server_Fire_Implementation() {
	if (!ensure(Barrel && ProjectileBlueprint)) return;
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBlueprint,
		Barrel->GetSocketLocation(FName("Projectile")),
		Barrel->GetSocketRotation(FName("Projectile"))
		);

	Projectile->LaunchProjectile(LaunchSpeed);
	Ammo--;
	LastFireTime = FPlatformTime::Seconds();
}

bool UTankAimingComponent::Server_Fire_Validate() {
	return (Ammo > 0);
}

void UTankAimingComponent::AimAt(FVector HitLocation) {
	if (!ensure(Barrel)) return;

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
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

EFiringState UTankAimingComponent::GetFiringState() const {
	return FiringState;
}

int32 UTankAimingComponent::GetAmmo() const {
	return Ammo;
}

#pragma endregion PUBLIC

#pragma region PROTECTED
void UTankAimingComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UTankAimingComponent, Ammo);
	DOREPLIFETIME(UTankAimingComponent, FiringState);
}
#pragma endregion PROTECTED

#pragma region PRIVATE
UTankAimingComponent::UTankAimingComponent() {
	PrimaryComponentTick.bCanEverTick = true;
	bReplicates = true;
}

void UTankAimingComponent::BeginPlay() {
	Super::BeginPlay();
	if (GetOwner()->Role == ROLE_Authority) {
		LastFireTime = FPlatformTime::Seconds();
	}
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (GetOwner()->Role == ROLE_Authority) {
		if (Ammo <= 0) {
			FiringState = EFiringState::NoAmmo;
		}
		else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds) {
			FiringState = EFiringState::Reloading;
		}
		else if (IsBarrelMoving()) {
			FiringState = EFiringState::Aiming;
		}
		else {
			FiringState = EFiringState::Locked;
		}
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	if (GetOwner()->Role < ROLE_Authority) {
		Server_MoveBarrelTowards(AimDirection);
	}

	if (!ensure(Barrel || Turret)) return;

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);

	if (FMath::Abs(DeltaRotator.Yaw) < 180) {
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else { // avoid going long-way around
		Turret->Rotate(-DeltaRotator.Yaw);
	}
}

void UTankAimingComponent::Server_MoveBarrelTowards_Implementation(FVector AimDirection) {
	MoveBarrelTowards(AimDirection);
}

bool UTankAimingComponent::Server_MoveBarrelTowards_Validate(FVector AimDirection) {
	return true;
}

bool UTankAimingComponent::IsBarrelMoving() {
	if (!ensure(Barrel)) return false;
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01);
}

#pragma endregion PRIVATE

