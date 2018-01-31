// Copyright Tony Faye

#include "TankAIController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "GameFramework/PlayerController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto AITank = GetPawn();

	if (!ensure(PlayerTank && AITank)) { return; }

	MoveToActor(PlayerTank, AcceptanceRadius);

	auto AimingComponent = AITank->FindComponentByClass<UTankAimingComponent>();

	AimingComponent->AimAt(PlayerTank->GetActorLocation()); // Get the location of the player

	if (AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire();
	}
}

