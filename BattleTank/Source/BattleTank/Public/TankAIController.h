// Copyright Tony Faye

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/*
 * TankAIController gives instructions to the AIController on what to do when
 */

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void SetPawn(APawn* InPawn) override; // Gets called when the pawn is possessed

	UPROPERTY(EditDefaultsOnly)
	float AcceptanceRadius = 8000.0f; // How close can the AI tank get to the player?

	UFUNCTION()
	void OnPossessedTankDeath();
};
