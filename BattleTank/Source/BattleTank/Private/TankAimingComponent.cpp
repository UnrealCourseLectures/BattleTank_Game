// Copyright B.A.Y. Joy-Works 2017

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false; 

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector OutHitLocation, float FiringSpeed)
{
	if (!Barrel) { return; }
	
	// Declaring Variables
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimResult = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		OutHitLocation,
		FiringSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace, //Must be present for unreal engine method bug to not occur
		FCollisionResponseParams::DefaultResponseParam,
		TArray<AActor*>(),
		false
	);

	// Making actual code functionallity to get AimResult/Solution
	if (bHaveAimResult)
	{
		//Calculate the OutLaunchVelocity
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveTurretTowards(AimDirection);
	}
	//We Don't do anything
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	if (!Barrel || !Turret) { return; }

	//Work-out difference between current barrel rotation, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	Barrel->Elevate(DeltaRotator.Pitch); 

	//Work-out difference between current turret rotation, and AimDirection
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto DeltaTurretRotation = AimAsRotator - TurretRotator;
	Turret->MoveTurret(DeltaTurretRotation.Yaw);
}
