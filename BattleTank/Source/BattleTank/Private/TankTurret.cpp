// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("%f: Turret Rotate Called at RelvativeSpeed: %s"), Time, RelativeSpeed);
	// Move the barrel the right amount, this frame

	// Given a max elevation speed and the frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);// Clamp RelativeSpeed to stop the barrel moving too quickly if people have a fast mouse. <float> is an optional type
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds; // Elevation change we need this frame
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange; // Unclamped elevation we will get each frame
	auto Rotation = FMath::Clamp<float>(RawNewRotation, -180, 180);

	SetRelativeRotation(FRotator(0, Rotation, 0)); // Move the turret
}