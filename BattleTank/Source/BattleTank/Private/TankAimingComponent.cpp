// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine.h"

UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile")); // Find the socket called Projectile on barrel. If it cant, it simply chooses the origin of Barrel

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity // Calculate the projectile velocity needed to hit where our crosshair is pointing
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal(); // Turns our out parameter into a unit vector
		MoveBarrelTowards(AimDirection);
		MoveTurretTowards(AimDirection);
	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f: No aim solve found"), Time);
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	if (!BarrelToSet) { return; }
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	if (!TurretToSet) { return; }
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// Calculate difference between current barrel rotation and Aim Direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation(); // Get the direction the barrel is looking (x axis) and convert it into a rotation
	auto AimAsRotator = AimDirection.Rotation(); // Convert our AimDirection
	auto DeltaRotator = AimAsRotator - BarrelRotator; // Get the difference between the two rotations. 

	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	auto TurretRotator = Turret->GetForwardVector().Rotation(); // Get the direction the turret is looking (x axis) and convert it into a rotation
	auto AimAsRotator = AimDirection.Rotation(); // Convert our AimDirection
	auto DeltaRotator = AimAsRotator - TurretRotator; // Get the difference between the two rotations. 
	Turret->Rotate(DeltaRotator.Yaw);
}