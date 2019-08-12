// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
//Variables
private:
	// Components
	//UPROPERTY(VisibleAnywhere, Category = "Components")
	//	USphereComponent* Wheel = nullptr;
	//UPROPERTY(VisibleAnywhere, Category = "Components")
	//	USphereComponent* Axle = nullptr;
	//UPROPERTY(VisibleAnywhere, Category = "Components")
	//	UPhysicsConstraintComponent* MassWheelConstraint = nullptr;
	//UPROPERTY(VisibleAnywhere, Category = "Components")
	//	UPhysicsConstraintComponent* AxleWheelConstraint = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		class UStaticMeshComponent* Wheel = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		class UPhysicsConstraintComponent* MassWheelConstraint = nullptr;

	float TotalForceMagnitudeThisFrame = 0;

//Functions
public:	
	ASprungWheel();
	virtual void Tick(float DeltaTime) override;
	void AddDrivingForce(float ForceMagnitude);

protected:
	virtual void BeginPlay() override;

private:
	void SetupConstraint();

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void ApplyForce();

};
