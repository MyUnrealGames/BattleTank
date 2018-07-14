// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"




void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = this->GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController doens't possesing a tank!"));
	}
	else
	{
		FString NameOfTank = ControlledTank->GetName();
		UE_LOG(LogTemp, Warning, TEXT("AIController possesing %s"), *NameOfTank);
	}
}


ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
