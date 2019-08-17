// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"

void UTankTrack::SetThrottle(float Throttle) {
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
	//Server_SetThrottle(Throttle);
}

void UTankTrack::Server_SetThrottle_Implementation(float Throttle) {
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}

bool UTankTrack::Server_SetThrottle_Validate(float Throttle) {
	return true;
}

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::DriveTrack(float CurrentThrottle) {
	auto Wheels = GetWheels();
	auto ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
	auto ForcePerWheel = ForceApplied / Wheels.Num();
	for (ASprungWheel* Wheel : Wheels) {
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}

// TODO: add if and private variable to store the wheels
TArray<ASprungWheel*> UTankTrack::GetWheels() const {
	TArray<ASprungWheel*> ResultArray;
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);
	for (USceneComponent* Child : Children) {
		auto SpawnPointChild = Cast<USpawnPoint>(Child);
		if (!SpawnPointChild) continue;

		AActor* SpawnedChild = SpawnPointChild->GetSpawnedActor();
		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
		if (!SprungWheel) continue;

		ResultArray.Add(SprungWheel);
	}
	return ResultArray;
}
