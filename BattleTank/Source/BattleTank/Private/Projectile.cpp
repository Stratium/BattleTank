// Copyright Tony Faye

#include "Projectile.h"
#include "Components/StaticMeshComponent.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true; // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh")); // Sets a default (unremovable) component on Projectile_BP
	SetRootComponent(CollisionMesh); // Makes our component the root component
	CollisionMesh->SetNotifyRigidBodyCollision(true); // Automatically checks "Simulation generates hit events"
	CollisionMesh->SetVisibility(false); // Automatically unchecks "Visible" in rendering

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast")); // Sets a default (unremovable) component on Projectile_BP
	LaunchBlast->AttachTo(RootComponent); // Attaches it to our root component, in this case our collision mesh

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement")); // Sets a default (unremovable) movement component on Tank_BP
	ProjectileMovement->bAutoActivate = false;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::LaunchProjectile(float Speed)
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovement->Activate();
}