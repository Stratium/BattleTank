// Copyright Tony Faye

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Locked,
	Aiming,
	Reloading
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

/*
 * TankAimingComponent takes a reference to the barrel, turret and projectiles to handle all aiming and firing code
 */

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

private:	
	UTankAimingComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	TSubclassOf<AProjectile> ProjectileBlueprint; // Alternatives https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/TSubclassOf/
	void MoveAimingTowards(FVector AimDirection);
	bool IsBarrelMoving();
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Firing") // EditAnywhere alternative https://wiki.unrealengine.com/UPROPERTY
	float LaunchSpeed = 4000;
	float ReloadTimeInSeconds = 3.0f;
	double LastFireTime = 0;
	FVector AimDirection;

public:	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
	UFUNCTION(BlueprintCallable)
	void Fire();
	void AimAt(FVector HitLocation);
};