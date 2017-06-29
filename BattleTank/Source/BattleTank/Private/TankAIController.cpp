// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerController = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto AIControlledTank = Cast<ATank>(GetPawn());
	
	if (PlayerController)
	{
		// Move towards the player
		MoveToActor(PlayerController, AcceptanceRadius);		

		// Aim At the player
		AIControlledTank->AimAt(PlayerController->GetActorLocation());

		AIControlledTank->Fire();
	}
}
