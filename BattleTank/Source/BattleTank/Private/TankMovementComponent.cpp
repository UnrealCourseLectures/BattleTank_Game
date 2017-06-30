// Copyright B.A.Y. Joy-Works 2017

#include "BattleTank.h"
#include "TankTracks.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTracks* LeftTrackToSet, UTankTracks* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Turn)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Turn);
	RightTrack->SetThrottle(-Turn);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto TanKForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	
	//Tells AI to move forward or backward, considering player location
	auto ForwardThrow = FVector::DotProduct(AIForwardIntention, TanKForward);
	IntendMoveForward(ForwardThrow);

	//Tells AI to move forward or backward, considering player location
	auto RightThrow = FVector::CrossProduct(TanKForward, AIForwardIntention).Z;
	IntendTurnRight(RightThrow);
}
