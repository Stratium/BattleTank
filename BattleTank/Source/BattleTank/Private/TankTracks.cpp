// Copyright Tony Faye

#include "TankTracks.h"
#include "Engine/World.h"

UTankTracks::UTankTracks()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTracks::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity()); // How fast we are moving sideways?
	auto CorrectionAccelleration = -SlippageSpeed / DeltaTime * GetRightVector(); // Work out an opposite speed over time, multiplied by our direction
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent()); // Find the root component of the tank
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAccelleration) / 2; // Multiply the total mass of the tank by our opposite acceleration. Divide by 2 because this will run on both our tracks
	TankRoot->AddForce(CorrectionForce); // Apply our force
}

void UTankTracks::SetThrottle(float Throttle)
{
	auto Name = GetName();
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation, NAME_None);
}