// Copyright Tony Faye

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/**
 * TankPlayerController handles all inputs and raycasts which it passes to the TankAimingComponent
 */

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup") // An event we can read from in Blueprint
	void FoundAimingComponent(UTankAimingComponent* AimingCompRef);

private:
	virtual void BeginPlay() override;
	/*	BeginPlay is defined in AActor, the parent of our player controller. Virtual means that children of a class can override this method down the inheritance tree.
		We therefore COPY AActor's BeginPlay function (virtual and all) and then add override to ensure this version of BeginPlay is being read by the compiler.		*/
	virtual void Tick(float DeltaTime) override;

	void AimTowardsCrosshair();

	// Getters
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.3333f;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.0f;
};
