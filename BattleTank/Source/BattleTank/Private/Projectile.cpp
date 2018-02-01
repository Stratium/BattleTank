// Copyright Tony Faye

#include "Projectile.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false; // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh")); // Sets a default (unremovable) component on Projectile_BP
	SetRootComponent(CollisionMesh); // Makes our component the root component
	CollisionMesh->SetNotifyRigidBodyCollision(true); // Automatically checks "Simulation generates hit events"
	CollisionMesh->SetVisibility(false); // Automatically unchecks "Visible" in rendering

	// TODO Update AttachTo to new API

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast")); // Sets a default (unremovable) component on Projectile_BP
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform); // Attaches it to our root component, in this case our collision mesh

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast")); // Sets a default (unremovable) component on Projectile_BP
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform); // Attaches it to our root component, in this case our collision mesh
	ImpactBlast->bAutoActivate = false; // Because we want to activate this manually

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement")); // Sets a default (unremovable) movement component on Tank_BP
	ProjectileMovement->bAutoActivate = false;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform); // Attaches it to our root component, in this case our collision mesh
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit); // Setup our on hit function
}

void AProjectile::LaunchProjectile(float Speed)
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovement->Activate();
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	ExplosionForce->FireImpulse(); // Cause objects within a blueprint specified radius to be forced away from the projectile
	SetRootComponent(ImpactBlast); // Change our root component because we want to destroy the collision mesh
	CollisionMesh->DestroyComponent(); // Remove this mesh, which also removes the model, to prevent them persisting in world after collision

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		this,
		&AProjectile::OnTimerExpire,
		DestroyDelay,
		false
		);
}

void AProjectile::OnTimerExpire()
{
	Destroy();
}