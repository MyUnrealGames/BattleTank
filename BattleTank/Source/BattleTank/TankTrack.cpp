// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"
#include "BattleTank.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"

UTankTrack::UTankTrack()
{
}

TArray<ASprungWheel*> UTankTrack::GetWheels()
{
	TArray<USceneComponent*> Children;
	GetChildrenComponents(false, Children);

	TArray<ASprungWheel*> Wheels;
	for(USceneComponent* Child: Children)
	{
		USpawnPoint* SpawnPoint = Cast<USpawnPoint>(Child);
		if (SpawnPoint)
		{
			ASprungWheel* Wheel = Cast<ASprungWheel>(SpawnPoint->GetSpawnedActor());
			
			if (Wheel)
				Wheels.Add(Wheel);
		}
		
	}
	return Wheels;
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	auto ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
	auto Wheels = GetWheels();
	auto ForcePerWheel = ForceApplied / Wheels.Num();

	for (ASprungWheel* Wheel : Wheels)
	{
		Wheel->ApplyDrivingForce(ForcePerWheel);
	}
}

void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}
