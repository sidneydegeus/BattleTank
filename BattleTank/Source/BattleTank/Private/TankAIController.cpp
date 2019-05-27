// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	ControlledTank = GetPawn();
	if (!ensure(ControlledTank)) return;
	TankAimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ensure(PlayerTank && ControlledTank && TankAimingComponent)) return;
	//  move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);

	TankAimingComponent->AimAt(PlayerTank->GetActorLocation());

	if (TankAimingComponent->GetFiringState() == EFiringState::Locked) {
		TankAimingComponent->Fire();
	}
}