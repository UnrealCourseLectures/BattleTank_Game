// Copyright B.A.Y. Joy-Works 2017

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Aiming,
	Reloading,
	Locked
};

//Forward Declaration
class UTankBarrel; 
class UTankTurret;
class AProjectile;

//Holds Barrel's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
		
	//Event Called in TankPlayerController.cpp to aim at crosshair
	void AimAt(FVector OutHitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire(); 

	bool IsBarrelMoving();
	
protected:
	UPROPERTY(BlueprintReadOnly)
	EFiringState FiringState = EFiringState::Reloading;

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void MoveTurretTowards(FVector AimDirection);

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
	float FiringSpeed = 4000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Fire") 
	float ReloadTimeinSeconds = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	double LastFireTime = 0;

	FVector AimDirection;
};
