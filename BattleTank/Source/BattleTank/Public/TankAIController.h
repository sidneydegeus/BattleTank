// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
// Variables
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float AcceptanceRadius = 8000;

private:
	APawn* ControlledTank = nullptr;
	UTankAimingComponent* TankAimingComponent = nullptr;

// Functions
public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	
private:
	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
		void OnPossessedTankDeath();
};
