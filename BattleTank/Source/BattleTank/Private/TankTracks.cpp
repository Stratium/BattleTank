// Copyright Tony Faye

#include "TankTracks.h"
#include "Engine/World.h"

void UTankTracks::SetThrottle(float Throttle)
{
	auto Name = GetName();
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation, NAME_None);
}