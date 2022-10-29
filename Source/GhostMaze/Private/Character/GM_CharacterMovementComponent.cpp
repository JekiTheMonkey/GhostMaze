#include "Character/GM_CharacterMovementComponent.h"

#include "Character/GM_PlayerCharacter.h"

void UGM_CharacterMovementComponent::TickComponent(
	float DeltaSeconds,
	ELevelTick TickType,
	FActorComponentTickFunction *ThisTickFunction)
{
	// Edit max walk speed before the speed computition
	EditMaxWalkSpeed();
	
	Super::TickComponent(DeltaSeconds, TickType, ThisTickFunction);
}

void UGM_CharacterMovementComponent::IncreaseSpeedRatio(float SpeedRatio)
{
	check(SpeedRatio > 0.f);
	
	ChangeSpeedRatio_Impl(OriginalMaxWalkSpeed * SpeedRatio);
}

void UGM_CharacterMovementComponent::DecreaseSpeedRatio(float SpeedRatio)
{
	check(SpeedRatio > 0.f);
	
	ChangeSpeedRatio_Impl(OriginalMaxWalkSpeed / SpeedRatio);
}

void UGM_CharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// Will be used to edit speed. HmCmc pretends that MaxWalkSpeed does NOT
	// change by any means except itself
	OriginalMaxWalkSpeed = MaxWalkSpeed;

	GmCharacter = CastChecked<AGM_BaseCharacter>(CharacterOwner);
}

void UGM_CharacterMovementComponent::ChangeSpeedRatio_Impl(float NewSpeed)
{
	// Keep the deceleration following the old ratio
	const float CurrentDecelerationRatio = MaxWalkSpeed / OriginalMaxWalkSpeed;
	MaxWalkSpeed = NewSpeed * CurrentDecelerationRatio;
	
	OriginalMaxWalkSpeed = NewSpeed;
}

void UGM_CharacterMovementComponent::EditMaxWalkSpeed()
{
	// Don't bother about other movement modes in this project
	if (MovementMode != EMovementMode::MOVE_Walking)
		return;
	
	float Angle = GmCharacter->GetAngleBetweenForwardAndVelocity();
	if (Angle == 0.f)
		return;

	// We don't care about whether it's left or right
	Angle = FMath::Abs(Angle);

	// 0.0 - min deceleration, 1.0 - max delecelation
	const float NormDecel = Angle / 180.f;

	// Example:
	// OrigSpeed 100, MaxSpeedOnOppositeDirectionNormilized 0.5, result 50
	const float MaxDecel = OriginalMaxWalkSpeed * MaxSpeedOnOppositeDirectionNormilized;

	// Compute final speed
	// Example: 100 - 50 * 0.5 (if angle is 90 and the norm value is 0.5)
	MaxWalkSpeed = OriginalMaxWalkSpeed - MaxDecel * NormDecel;
}
