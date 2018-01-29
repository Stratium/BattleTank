// Copyright Tony Faye

#include "TankBarrel.h"
#include "Engine.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	auto Time = GetWorld()->GetTimeSeconds();

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);// Clamp RelativeSpeed to stop the barrel moving too quickly if people have a fast mouse. <float> is an optional type

	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds; // Elevation change we need this frame
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange; // Unclamped elevation we will get each frame
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinimumElevationDegrees, MaximumElevationDegrees); // Elevation clamped to our min and max elevations. <float> is an optional type
	
	SetRelativeRotation(FRotator(Elevation, 0, 0)); // Move the barrel
}