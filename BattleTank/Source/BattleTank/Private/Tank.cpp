// Copyright Tony Faye

#include "Tank.h"
#include "Engine.h"


ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	int DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	auto DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	UE_LOG(LogTemp, Warning, TEXT("Damage Amount = %f, DamageToApply = %i"), DamageAmount, DamageToApply);
	CurrentHealth -= DamageToApply;

	if (CurrentHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("DED.JPG"));
	}

	return DamageToApply;
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth; // Converts our int32 values into floats and turns them into a percentage
}
