// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	ATank* PlayerTank = PlayerPawn ? Cast<ATank>(PlayerPawn) : nullptr;
	if (PlayerTank)
	{
		ATank* ControlledTank = Cast<ATank>(GetPawn());

		// Aim towards the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		ControlledTank->Fire(); // TODO limit firing rate
	}
}

