// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

private:
	ATank(); // Sets default values for this pawn's properties
	virtual void BeginPlay() override; // Called when the game starts or when spawned
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	TSubclassOf<AProjectile> ProjectileBlueprint; // Alternatives https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/TSubclassOf/
	float ReloadTimeInSeconds = 3.0f;
	double LastFireTime = 0;

	UTankBarrel* Barrel = nullptr; // TODO Remove barrel reference from tank.h

	UPROPERTY(EditDefaultsOnly, Category = "Firing") // TODO Remove launchspeed from tank.cpp
	float LaunchSpeed = 4000;

public:
	UFUNCTION(BlueprintCallable)
	void Fire();
};