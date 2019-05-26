// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "StaticLibrary.h"
#include "DrawDebugHelpers.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) return;
	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() {
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) return;
	
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) {
		AimingComponent->AimAt(HitLocation);
		//GetControlledTank()->FindComponentByClass<UTankAimingComponent>()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(
		ViewportSizeX * CrosshairXLocation,
		ViewportSizeY * CrosshairYLocation
	);

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const{
	FVector CameraWorldLocation; // Not used, but must be passed in
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetPawn());
	bool bLineTraceHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility,
		CollisionParams
	);

	if (bLineTraceHit) {
		HitLocation = HitResult.Location;
		//DrawDebugLine(GetWorld(), StartLocation, HitLocation, FColor::Green, false, 1, 0, 1); //
		return true;
	}
	HitLocation = EndLocation;
	//DrawDebugLine(GetWorld(), StartLocation, HitLocation, FColor::Red, false, 1, 0, 1); //
	return false;
}