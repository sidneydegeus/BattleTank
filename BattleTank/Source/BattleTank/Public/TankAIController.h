// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
// Variables
private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float AcceptanceRadius = 3000;

// Functions
public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	
};
