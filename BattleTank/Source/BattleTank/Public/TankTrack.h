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
	UFUNCTION(BlueprintCallable, Category = Input)
		void SetThrottle(float Throttle);

	// Max force per track, in Newtons
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 400000;

private:
	float CurrentThrottle = 0;

// Functions
private:
	UTankTrack();
	virtual void BeginPlay() override;

	void DriveTrack();
	void ApplySidewaysForce();
	
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

};
