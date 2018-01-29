// Forget copyrights, do whatever you want with these files

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerPawn = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto AITank = Cast<ATank>(GetPawn());

	if (ensure(PlayerPawn))
	{
		MoveToActor(PlayerPawn, AcceptanceRadius);
		AITank->AimAt(PlayerPawn->GetActorLocation()); // Get the location of the player
		AITank->Fire();
	}
}

