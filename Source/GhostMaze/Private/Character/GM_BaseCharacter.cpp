#include "Character/GM_BaseCharacter.h"

#include "Character/GM_RunComponent.h"

AGM_BaseCharacter::AGM_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	RunComponent = CreateDefaultSubobject<UGM_RunComponent>(TEXT("Run Component"));
}

// Note: Can be cached since the function is called from two sources each frame
float AGM_BaseCharacter::GetAngleBetweenForwardAndVelocity() const
{
	FVector Velocity = GetVelocity();
	if (Velocity.IsZero())
		return 0.f;

	const FVector Forward = GetActorForwardVector();
	Velocity = Velocity.GetSafeNormal();
	
	const float Dot = FVector::DotProduct(Velocity, Forward);
	const FVector Cross(FVector::CrossProduct(Velocity, Forward));

	const float AcosDeg = FMath::RadiansToDegrees(FMath::Acos(Dot));
	
	return Cross.IsZero() ? (AcosDeg) : (AcosDeg * FMath::Sign(Cross.Z));
}
