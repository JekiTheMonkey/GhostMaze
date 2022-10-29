#pragma once

#include "CoreMinimal.h"
#include "Character/GM_BaseCharacter.h"

#include "GM_PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class GHOSTMAZE_API AGM_PlayerCharacter : public AGM_BaseCharacter
{
	GENERATED_BODY()

public:
	AGM_PlayerCharacter();

	//~ Begin APawn Interface.
	virtual void SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) override;
	//~ End APawn Interface

protected:
	//~ Begin AActor Interface.
	virtual void BeginPlay() override;
	//~ End AActor Interface

private:
	UFUNCTION()
	void OnMoveForward(float Ratio);
	
	UFUNCTION()
	void OnMoveRight(float Ratio);

	UFUNCTION()
	void OnLookUp(float Ratio);

	UFUNCTION()
	void OnLookRight(float Ratio);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components",
		meta=(AllowPrivateAccess="true"))
	TObjectPtr<USpringArmComponent> CameraBoom = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components",
		meta=(AllowPrivateAccess="true"))
	TObjectPtr<UCameraComponent> Camera = nullptr;
};
