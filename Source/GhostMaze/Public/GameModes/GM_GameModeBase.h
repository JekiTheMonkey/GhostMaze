#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "GM_GameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDynamicMulticastDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameOverDelegate, bool, bWon);

UENUM(BlueprintType)
enum class EGM_GameState : uint8
{
	InProgress,
	Won,
	Lost
};

UCLASS()
class GHOSTMAZE_API AGM_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGM_GameModeBase();

	EGM_GameState GetGameState() const { return HmGameState; }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="GM|Game Mode Base")
	void Restart();
	virtual void Restart_Implementation();

protected:
	//~ Begin AActor Interface.
	virtual void BeginPlay() override;
	//~ End AActor Interface

	UFUNCTION(BlueprintNativeEvent, Category="GM|Game Mode Base")
	void OnGameOver(bool bSuccess);
	virtual void OnGameOver_Implementation(bool bSuccess);

private:
	void FinishGame(bool bSuccess);
	
public:
	UPROPERTY(BlueprintAssignable)
	FGameOverDelegate GameOverDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FDynamicMulticastDelegate RestartDelegate;

private:
	UPROPERTY(BlueprintReadOnly, Category="GM|Game Mode Base",
		meta=(AllowPrivateAccess="true"))
	EGM_GameState HmGameState = EGM_GameState::InProgress;
};
