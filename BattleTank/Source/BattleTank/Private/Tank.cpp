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