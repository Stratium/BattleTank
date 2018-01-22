// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	// Check to make sure an AI is controlling the tank
	auto AIControlledTank = GetAIControlledTank();
	auto PlayerTank = GetPlayerPawn();

	if (!AIControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("AI not found on tank %s"), (*AIControlledTank->GetName()))
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("AI possessing tank %s"), (*AIControlledTank->GetName()))
	}

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("AI %s did not find a player"), *(AIControlledTank->GetName()))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI %s found player: %s"), *(AIControlledTank->GetName()), *(PlayerTank->GetName()))
	}
}

ATank* ATankAIController::GetAIControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerPawn() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}

