// Copyright Psyke Ltd.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for firing state
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};

// Forward Declaration
class UTankBarrel; 
class UTankTurret; 
class AProjectile;

// Hold barrel's properties and Elevate method
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable, Category="Setup")
	void Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet, TSubclassOf<AProjectile> ProjectileBlueprintToSet);

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	EFiringState GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 GetAmmo() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

	FVector AimDirection;

private:
	UTankAimingComponent();
	void MoveBarrelTowards();
	bool IsBarrelMoving();

	UTankBarrel * Barrel = nullptr;
	UTankTurret * Turret = nullptr;

	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 8000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	double ReloadTimeInSeconds = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 Ammo = 20;

	double LastFireTime = 0;

	

};
