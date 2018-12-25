// Copyright Psyke Ltd.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Pase new include above
//#include "Engine/Classes/GameFramework/Actor.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent();

private:
	ATank();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth = StartingHealth;


	// Called by the engine when actor damage is dealt
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
	
};
