// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTracks.generated.h"

/**
 * 
 */
UCLASS( meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTracks : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	// Set a throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);
	
	// Max force per track, in Newtons [Force = Mass(SI, kilograms) * Acceleration(SI, meters per seconds)]
	UPROPERTY(EditDefaultsOnly, Category = "DrivingForce")
	float TrackMaxDrivingForce = 400000; // Assume 40ton tank, 1g acceleration
};
