// Copyright Tony Faye

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

private:
	ATank(); // Sets default values for this pawn's properties
	virtual void BeginPlay() override; // Called when the game starts or when spawned
};