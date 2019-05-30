// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

//Variables
private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32 MaxHealth = 100;

	int32 CurrentHealth;

//Functions
public:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;
	
	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealthPercentage() const;

	//UFUNCTION()
	FTankDelegate OnDeath;

private:
	ATank();
	virtual void BeginPlay() override;
};
