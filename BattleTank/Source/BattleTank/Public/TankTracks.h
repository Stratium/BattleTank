// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTracks.generated.h"

/**
 * Tank Tracks are used to set maximum driving force and to apply forces to the tank. It is based from StaticMeshComponent and should be duplicated in all instances of Tank, one for each track.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTracks : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float TrackMaxDrivingForce = 400000; // Assume 40 ton tank and 1g acceleration	
};
