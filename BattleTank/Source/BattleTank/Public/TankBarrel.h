// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
* Tank Barrel is used to elevate the static mesh of the barrel to face the pitch of the mouse. It is based from StaticMeshComponent.
*/
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downward movement, +1 is max upward movement
	void Elevate(float RelativeSpeed);	

private:
	UPROPERTY(EditDefaultsOnly)
	float MaxDegreesPerSecond = 20; // Sensible default

	UPROPERTY(EditDefaultsOnly)
	float MinimumElevationDegrees = 0;

	UPROPERTY(EditDefaultsOnly)
	float MaximumElevationDegrees = 40;
};
