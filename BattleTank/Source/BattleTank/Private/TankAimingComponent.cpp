// Copyright B.A.Y. Joy-Works 2017

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true; 

	// ...
}

void UTankAimingComponent::BeginPlay()
{
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeinSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if(IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	FVector BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01);
}

void UTankAimingComponent::Fire()
{
	if (FiringState != EFiringState::Reloading)
	{
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		FVector BarrelLocation = Barrel->GetSocketLocation(FName("Projectile"));
		FRotator BarrelRotation = Barrel->GetSocketRotation(FName("Projectile"));
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, BarrelLocation, BarrelRotation, FActorSpawnParameters());

		Projectile->LaunchProjectile(FiringSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

void UTankAimingComponent::AimAt(FVector OutHitLocation)
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
		AimDirection = OutLaunchVelocity.GetSafeNormal();
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
