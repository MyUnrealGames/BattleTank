// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "CoreMinimal.h"
#include "TankAIController.generated.h"

// Forward Declarations
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	UTankAimingComponent* AimingComponent = nullptr;

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	// How close can the AI tank get
	float AcceptanceRadius = 3000.f;
};
