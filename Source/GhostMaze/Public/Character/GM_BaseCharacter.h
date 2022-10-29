#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "GM_BaseCharacter.generated.h"

class UGM_RunComponent;

UCLASS()
class GHOSTMAZE_API AGM_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AGM_BaseCharacter();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="GM|Character")
	float GetAngleBetweenForwardAndVelocity() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components",
		meta=(AllowPrivateAccess="true"))
	TObjectPtr<UGM_RunComponent> RunComponent = nullptr;
};
