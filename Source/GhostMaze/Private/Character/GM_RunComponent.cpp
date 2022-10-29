#include "Character/GM_RunComponent.h"

#include "GM_Log.h"
#include "Character/GM_CharacterMovementComponent.h"

UGM_RunComponent::UGM_RunComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UGM_RunComponent::TickComponent(
	float DeltaSeconds, 
	ELevelTick TickType, 
	FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaSeconds, TickType, ThisTickFunction);

	if (!IsValid(OwnerGmCmc))
		return;

	const bool bIsVelocityNearlyZero = OwnerGmCmc->Velocity.IsNearlyZero();
	if (!bWantsRunning || !CanRun() || bIsVelocityNearlyZero)
	{
		// Input is not pressed anymore or not enough stamina will cause us to stop
		if (bIsRunning)
		{
			StopRunning_Impl();
		}

		// Regenerate stamina
		const float NewStamina =
			FMath::Min(MaxStamina, CurrentStamina + (StaminaRegeneration * DeltaSeconds));
		if (NewStamina != CurrentStamina)
			SetStamina(NewStamina);
		
		return;
	}

	// Start running
	if (!bIsRunning)
	{
		StartRunning_Impl();
	}

	// Consume stamina
	SetStamina(FMath::Max(0.f, CurrentStamina - (StaminaConsumption * DeltaSeconds)));
}

void UGM_RunComponent::TryStartRunning()
{
	bWantsRunning = true;
}

void UGM_RunComponent::StopRunning()
{
	bWantsRunning = false;
}

bool UGM_RunComponent::CanRun() const
{
	if (CurrentStamina <= 0.f)
		return false;
		
	if (!bRanOutOfStamina)
		return true;
	
	return GetStaminaRatio() > StaminaThresholdAfterCompleteConsumptionRatio;
}

void UGM_RunComponent::BeginPlay()
{
	Super::BeginPlay();

	// Start with full stamina
	SetStamina(MaxStamina);

	AActor *Owner = GetOwner();
	check(IsValid(Owner));
	
	auto GmCmc = Owner->GetComponentByClass(UGM_CharacterMovementComponent::StaticClass());
	if (!IsValid(GmCmc))
	{
		GMS_WARN("GM Character movement component on owner [%s] is invalid", *Owner->GetName());
		return;
	}
	
	OwnerGmCmc = CastChecked<UGM_CharacterMovementComponent>(GmCmc);
}

void UGM_RunComponent::StartRunning_Impl()
{
	check(!bIsRunning);

	OwnerGmCmc->IncreaseSpeedRatio(SpeedBoost);
	
	bIsRunning = true;
	RunStartDelegate.Broadcast();
}

void UGM_RunComponent::StopRunning_Impl()
{
	check(bIsRunning);
	
	OwnerGmCmc->DecreaseSpeedRatio(SpeedBoost);
	
	bIsRunning = false;
	
	// Player has to push the button once again
	bWantsRunning = false;
	
	RunStopDelegate.Broadcast();

	// Owner will not be able to run for some time
	if (CurrentStamina <= 0.f)
	{
		bRanOutOfStamina = true;
		RanOutOfStamina.Broadcast();
	}
}

void UGM_RunComponent::SetStamina(float Value)
{
	const float OldValue = CurrentStamina;
	CurrentStamina = Value;

	if (bRanOutOfStamina && CurrentStamina / MaxStamina >= StaminaThresholdAfterCompleteConsumptionRatio)
		bRanOutOfStamina = false;
		
	StaminaChangedDelegate.Broadcast(CurrentStamina, OldValue, GetStaminaRatio());
}
