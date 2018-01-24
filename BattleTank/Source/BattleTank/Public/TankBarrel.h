// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downward movement, +1 is max upward movement
	void Elevate(float RelativeSpeed);	

private:
	UPROPERTY(EditAnywhere)
	float MaxDegreesPerSecond = 20; // Sensible default

	UPROPERTY(EditAnywhere)
	float MinimumElevationDegrees = 0;

	UPROPERTY(EditAnywhere)
	float MaximumElevationDegrees = 40;
};