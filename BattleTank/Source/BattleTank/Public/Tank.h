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

	UPROPERTY(Replicated)
		FVector ReplicatedLocation;

	UPROPERTY(Replicated)
		FRotator ReplicatedRotation;

//Functions
public:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;
	
	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealthPercentage() const;

	FTankDelegate OnDeath;

protected:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

private:
	ATank();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
