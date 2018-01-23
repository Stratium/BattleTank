// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "BattleTank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay(); // Ensures that this is being called when overriding methods from higher in the inheritance tree

	// Check to make sure we are possessing a tank
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController not possessing a tank"));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn()); // Get the tank that is being possessed
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector OutHitLocation; // OUT Parameter

	if (GetSightRayHitLocation(OutHitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *OutHitLocation.ToString());
		// TODO Rotate barrel to face HitLocation
		GetControlledTank()->AimAt(OutHitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	// De-project the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line trace along that look direction, see what we hit (up to max range)
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // We don't need this, but it has to be passed into a deproject anyway.
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection); // Get the XYZ world coordinates based on our parameters
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation(); // Start our line trace at the camera's location
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange); // End it 10km from our start location, in the direction of LookDirection

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult, // Where we store our hit
		StartLocation, // Where the trace starts
		EndLocation, // Where the trace ends
		ECollisionChannel::ECC_Visibility) // Tells our trace what to collide with. In this case, everything we can see
		)
	{
		OutHitLocation = HitResult.Location;
		return true;
	}
	else
	{
		OutHitLocation = FVector(0);
		return false;
	}
}