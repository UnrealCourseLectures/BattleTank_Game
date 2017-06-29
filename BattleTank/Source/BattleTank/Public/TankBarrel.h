// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS( meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downward speed and +1 is max upward speed
	void Elevate(float RelativeSpeed);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDegreesPerSecond = 8.f; //Sensible default

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxElevationInDegrees = 40.f; //Sensible default

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MinElevationInDegrees = 0.f; //Sensible default
};
