// Forget copyrights, do whatever you want with these files

#include "TankMovementComponent.h"
#include "TankTracks.h"

void UTankMovementComponent::Initialise(UTankTracks* LeftTrackToSet, UTankTracks* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call Super as we are replacing the functionality
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal(); // Gets a unit direction in the direction the actor is facing in the world
	auto AIForwardIntention = MoveVelocity.GetSafeNormal(); // Gets the velocity in unit directions the AI wishes to move in the navmesh

	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	auto RightThrowVector = FVector::CrossProduct(TankForward, AIForwardIntention);
	float RightThrow = RightThrowVector.Z;
	IntendTurnRight(RightThrow);
	IntendMoveForward(ForwardThrow);
}