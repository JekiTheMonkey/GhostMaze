#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "GM_CharacterMovementComponent.generated.h"

class AGM_BaseCharacter;

UCLASS()
class GHOSTMAZE_API UGM_CharacterMovementComponent : 
	public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	virtual void TickComponent(
		float DeltaSeconds,
		ELevelTick TickType, 
		FActorComponentTickFunction *ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category="GM|Character Movement")
	void IncreaseSpeedRatio(float SpeedRatio);
	
	UFUNCTION(BlueprintCallable, Category="GM|Character Movement")
	void DecreaseSpeedRatio(float SpeedRatio);

protected:
	virtual void BeginPlay() override;

private:
	void ChangeSpeedRatio_Impl(float NewSpeed);
	void EditMaxWalkSpeed();

private:
	UPROPERTY()
	TObjectPtr<AGM_BaseCharacter> GmCharacter = nullptr;

	UPROPERTY(EditDefaultsOnly, Category="Character Movement: Walking",
		meta=(ClampMin="0.0", ClampMax="1.0"))
	float MaxSpeedOnOppositeDirectionNormilized = 0.5f;
	
	float OriginalMaxWalkSpeed = 0.f;
};
