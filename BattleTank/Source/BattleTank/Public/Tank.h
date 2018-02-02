// Copyright Tony Faye

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Actor.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

private:
	ATank(); // Sets default values for this pawn's properties
	virtual void BeginPlay() override; // Called when the game starts or when spawned
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32 StartingHealth = 100;
	UPROPERTY(VisibleAnywhere, Category = "Health")
		int32 CurrentHealth = StartingHealth;

public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override; // Called automatically when actor damage is dealt

	// Returns current health as a percentage of starting health, between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;
};