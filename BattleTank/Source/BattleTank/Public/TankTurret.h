// Copyright Tony Faye

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * Tank Turret is used to rotate the static mesh of the turret to face the yaw of the mouse. It is based from StaticMeshComponent.
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision")) // You can disable Blueprint categories on models like this
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// -1 is max downward movement, +1 is max upward movement
	void Rotate(float RelativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly)
		float MaxDegreesPerSecond = 20; // Sensible default
};