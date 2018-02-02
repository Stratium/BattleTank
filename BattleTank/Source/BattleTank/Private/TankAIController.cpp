// Copyright Tony Faye

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h" // So we can implement OnDeath
#include "TankAimingComponent.h"
#include "GameFramework/PlayerController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// Subscribe our local method to the tanks death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	if (!GetPawn()) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto AITank = GetPawn();

	if (!(PlayerTank && AITank)) { return; }

	MoveToActor(PlayerTank, AcceptanceRadius);

	auto AimingComponent = AITank->FindComponentByClass<UTankAimingComponent>();

	AimingComponent->AimAt(PlayerTank->GetActorLocation()); // Get the location of the player

	if (AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire();
	}
}