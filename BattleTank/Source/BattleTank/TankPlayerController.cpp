// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"



void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = this->GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller doens't possesing a tank!"));
	}
	else
	{
		FString NameOfTank = ControlledTank->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Player Controller possesing %s"), *NameOfTank);
	}
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
