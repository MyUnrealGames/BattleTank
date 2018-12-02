// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	// Move to player
	if (!ensure(PlayerTank))
		return;
	MoveToActor(PlayerTank, AcceptanceRadius);
	
	// Aim towards the player
	if (!ensure(AimingComponent))
		return;
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	AimingComponent->Fire(); // TODO limit firing rate
}

