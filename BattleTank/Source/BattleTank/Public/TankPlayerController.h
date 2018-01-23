// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "TankPlayerController.generated.h"

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;	

	virtual void BeginPlay() override;
	/*	BeginPlay is defined in AActor, the parent of our player controller. Virtual means that children of a class can override this method down the inheritance tree.
		We therefore COPY AActor's BeginPlay function (virtual and all) and then add override to ensure this version of BeginPlay is being read by the compiler.		*/
	virtual void Tick(float DeltaTime) override;

private:
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.3333f;
};
