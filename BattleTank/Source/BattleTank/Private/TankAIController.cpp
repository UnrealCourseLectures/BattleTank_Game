// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerController = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto AIControlledTank = GetPawn();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	
	if (PlayerController)
	{
		// Move towards the player
		MoveToActor(PlayerController, AcceptanceRadius);		

		// Aim At the player
		AimingComponent->AimAt(PlayerController->GetActorLocation());

		if(AimingComponent->GetFiringState() == EFiringState::Locked)
		{
			AimingComponent->Fire(); 
		}
	}
}
