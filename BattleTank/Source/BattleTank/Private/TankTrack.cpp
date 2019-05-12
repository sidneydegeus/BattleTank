// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "StaticLibrary.h"

void UTankTrack::SetThrottle(float Throttle) {
	auto Name = GetName();
	FString s = FString::Printf(TEXT("%s throttle: %f"), *Name, Throttle);
	UStaticLibrary::PrintWarning(s, FString(__FILE__), __LINE__);

	auto ClampedThrottle = FMath::Clamp<float>(Throttle, -1, +1);
	auto ForceApplied = GetForwardVector() * ClampedThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}