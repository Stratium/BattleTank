// Copyright Tony Faye

#include "TankTracks.h"
#include "Engine/World.h"

UTankTracks::UTankTracks()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTracks::BeginPlay()
{
	Super::BeginPlay(); // Ensures that this is being called when overriding methods from higher in the inheritance tree
	OnComponentHit.AddDynamic(this, &UTankTracks::OnHit);
}

void UTankTracks::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTracks::DriveTrack()
{
	auto Name = GetName();
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation, NAME_None);
}


void UTankTracks::CorrectSlippage()
{
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity()); // How fast we are moving sideways?
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAccelleration = -SlippageSpeed / DeltaTime * GetRightVector(); // Work out an opposite speed over time, multiplied by our direction
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent()); // Find the root component of the tank
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAccelleration) / 2; // Multiply the total mass of the tank by our opposite acceleration. Divide by 2 because this will run on both our tracks
	TankRoot->AddForce(CorrectionForce); // Apply our force
}

void UTankTracks::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack();
	CorrectSlippage();
	CurrentThrottle = 0;
}