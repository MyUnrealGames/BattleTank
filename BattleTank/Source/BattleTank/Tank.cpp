// Copyright Psyke Ltd.

#include "Tank.h"
#include "BattleTank.h"

float ATank::GetHealthPercent()
{
	return (float)CurrentHealth/ (float)StartingHealth;
}

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp<int32>(DamagePoints, 0, CurrentHealth);
	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("NOOOL I DIED :("));
	}
	UE_LOG(LogTemp, Warning, TEXT("DamageAmount: %f, DamageToApply: %i, Health (AfterHit): %i"), DamageAmount, DamageToApply, CurrentHealth);

	return DamageToApply;
}

