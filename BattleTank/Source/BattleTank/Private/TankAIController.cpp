// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	ControlledTank = GetPawn();
	if (!ensure(ControlledTank)) return;
	TankAimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::SetPawn(APawn* InPawn) {
	Super::SetPawn(InPawn);
	if (InPawn) {
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) return;

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath() {
	if (!ensure(GetPawn())) return;
	GetPawn()->DetachFromControllerPendingDestroy();
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