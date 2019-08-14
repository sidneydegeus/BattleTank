// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

// Variables
public:
	// Max force per track, in Newtons
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 40000000;

// Functions
public:
	UFUNCTION(BlueprintCallable, Category = Input)
		void SetThrottle(float Throttle);

	UFUNCTION(Server, Reliable, WithValidation)
		void Server_SetThrottle(float Throttle);
		void Server_SetThrottle_Implementation(float Throttle);
		bool Server_SetThrottle_Validate(float Throttle);

private:
	UTankTrack();
	void DriveTrack(float CurrentThrottle);
	TArray<class ASprungWheel*> GetWheels() const;
};
