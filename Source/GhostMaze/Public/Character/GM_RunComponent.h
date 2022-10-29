#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "GM_RunComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDynamicMulticastSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FStaminaChangedSignature, float, NewValue, float, OldValue, float, Ratio);

class UGM_CharacterMovementComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GHOSTMAZE_API UGM_RunComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGM_RunComponent();

	virtual void TickComponent(
		float DeltaSeconds, 
		ELevelTick TickType,
		FActorComponentTickFunction *ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category="GM|Run Component")
	void TryStartRunning();
	
	UFUNCTION(BlueprintCallable, Category="GM|Run Component")
	void StopRunning();

	float GetStamina() const { return CurrentStamina; }
	float GetMaxStamina() const { return MaxStamina; }
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="GM|Run Component")
	float GetStaminaRatio() const { return CurrentStamina / MaxStamina; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="GM|Run Component")
	bool CanRun() const;

protected:
	//~ Begin AActor Interface.
	virtual void BeginPlay() override;
	//~ End AActor Interface

private:
	void StartRunning_Impl();
	void StopRunning_Impl();

	void SetStamina(float Value);

public:
	UPROPERTY(BlueprintAssignable)
	FDynamicMulticastSignature RunStartDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FDynamicMulticastSignature RunStopDelegate;

	UPROPERTY(BlueprintAssignable)
	FDynamicMulticastSignature RanOutOfStamina;
	
	UPROPERTY(BlueprintAssignable)
	FStaminaChangedSignature StaminaChangedDelegate;

private:
	UPROPERTY()
	TObjectPtr<UGM_CharacterMovementComponent> OwnerGmCmc = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="GM|Run Component",
		meta=(AllowPrivateAccess="true", ClampMin="1.0"))
	float MaxStamina = 100.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="GM|Run Component",
		meta=(AllowPrivateAccess="true", ClampMin="0.0"))
	float StaminaRegeneration = 10.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="GM|Run Component",
		meta=(AllowPrivateAccess="true", ClampMin="0.0"))
	float StaminaConsumption = 16.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="GM|Run Component",
		meta=(AllowPrivateAccess="true", ClampMin="0.0"))
	float SpeedBoost = 1.5f;
	
	UPROPERTY(BlueprintReadOnly, Category="GM|Run Component",
		meta=(AllowPrivateAccess="true"))
	float CurrentStamina = 0.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="GM|Run Component",
		meta=(AllowPrivateAccess="true", ClampMin="0.0", ClampMax="1.0"))
	float StaminaThresholdAfterCompleteConsumptionRatio = 0.3f;

	bool bRanOutOfStamina = false;

	bool bWantsRunning = false;

	UPROPERTY(BlueprintReadOnly, Category="GM|Run Component",
		meta=(AllowPrivateAccess="true"))
	bool bIsRunning = false;
};
