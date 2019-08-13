// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "SprungWheel.h"

void UTankTrack::SetThrottle(float Throttle) {
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
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


TArray<ASprungWheel*> UTankTrack::GetWheels() const {
	return TArray<class ASprungWheel*>();
}
