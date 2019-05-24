// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "StaticLibrary.h"

void UTankTrack::SetThrottle(float Throttle) {
	auto ClampedThrottle = FMath::Clamp<float>(Throttle, -1, +1);
	auto ForceApplied = GetForwardVector() * ClampedThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}