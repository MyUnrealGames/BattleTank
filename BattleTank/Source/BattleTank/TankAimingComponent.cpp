// Copyright Psyke Ltd.

#include "TankAimingComponent.h"
#include "BattleTank.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "TankTurret.h"


UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (FiringState != EFiringState::OutOfAmmo)
	{
		if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
		{
			FiringState = EFiringState::Reloading;
		}
		else if (IsBarrelMoving())
		{
			FiringState = EFiringState::Aiming;
		}
		else
		{
			FiringState = EFiringState::Locked;
		}
	}
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

int UTankAimingComponent::GetAmmo() const
{
	return Ammo;
}

void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace // Parameter must be present to prevent bug !
	);
	
	// Calculate the OutLaunchVelocity
	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
	
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel)) { return; }
	if (!ensure(Turret)) { return; }
	// Work-out difference betweeen current barrel rotation and AimDirection
	// Get Forward Vector is the rotation only by the x axis
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;

	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *(AimAsRotator.ToString()))
	Barrel->Elevate(DeltaRotator.Pitch);
	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
	
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel))
		return false;
	
	return !(AimDirection.Equals(Barrel->GetForwardVector(), 0.01));
}


void UTankAimingComponent::Fire()
{	
	if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming)
	{
		// Spawn a projectile at the socket location of barrel
		if (!ensure(Barrel))
			return;
		if (!ensure(ProjectileBlueprint))
			return;
		FVector Location = Barrel->GetSocketLocation(FName("Projectile"));
		FRotator Rotation = Barrel->GetSocketRotation(FName("Projectile"));
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Location,
			Rotation,
			FActorSpawnParameters());

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		--Ammo;
		if (Ammo == 0)
		{
			FiringState = EFiringState::OutOfAmmo;
		}
	}

}
