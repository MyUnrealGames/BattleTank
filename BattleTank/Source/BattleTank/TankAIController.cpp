// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* PlayerTank = this->GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController can't find PlayerTank!"));
	}
	else
	{
		FString NameOfTank = PlayerTank->GetName();
		UE_LOG(LogTemp, Warning, TEXT("AIController found PlayerTank named: %s"), *NameOfTank);
	}
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	ATank* PlayerTank = GetPlayerTank();
	if (PlayerTank)
	{
		// TODO : Move towards the player

		// Aim towards the player
		GetControlledTank()->AimAt(PlayerTank->GetActorLocation());

		// Fire if ready
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn)
	{
		return nullptr;
	}
	return Cast<ATank>(PlayerPawn);
}
