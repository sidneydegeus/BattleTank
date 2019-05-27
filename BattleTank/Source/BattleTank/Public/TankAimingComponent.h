// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked,
	NoAmmo
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

// Holds barrel's properties and elevate method
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

// Variables	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState FiringState = EFiringState::Reloading;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 100000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	double LastFireTime = 0;
	FVector AimDirection;
	int Ammo = 3;

// Functions
public:	
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialize(UTankBarrel* TankBarrelToSet, UTankTurret* TankTurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();

	UFUNCTION(BlueprintCallable, Category = "Firing")
		int GetAmmo() const;

	void AimAt(FVector HitLocation);
	EFiringState GetFiringState() const;


private:
	UTankAimingComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void MoveBarrelTowards(FVector AimDirection);	
	bool IsBarrelMoving();
};
