// Copyright B.A.Y. Joy-Works 2017

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Forward Declarations
class UTankAimingComponent;
class UTankBarrel; 
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	//Event Called in TankPlayerController.cpp to aim at crosshair
	void AimAt(FVector OutHitLocation);

protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
	float FiringSpeed = 4000.f; 

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
	float ReloadTimeinSeconds = 3;

	// Reference for spawning Projectile_BP
	UTankBarrel* Barrel = nullptr;

	double LastFireTime = 0;
};
