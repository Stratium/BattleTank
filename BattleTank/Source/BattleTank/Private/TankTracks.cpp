// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTracks.h"
#include "Engine/World.h"

void UTankTracks::SetThrottle(float Throttle)
{
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s thottle: %f"), *Name, Throttle);
	
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation, NAME_None);
}