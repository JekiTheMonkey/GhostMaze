#include "GameModes/GM_GameModeBase.h"

#include "GM_Log.h"
#include "Character/GM_PlayerCharacter.h"
#include "Character/GM_PlayerController.h"
#include "Kismet/GameplayStatics.h"

AGM_GameModeBase::AGM_GameModeBase()
{
	DefaultPawnClass = AGM_PlayerCharacter::StaticClass();
	PlayerControllerClass = AGM_PlayerController::StaticClass();
}

void AGM_GameModeBase::Restart_Implementation()
{
	HmGameState = EGM_GameState::InProgress;

	RestartDelegate.Broadcast();
}

void AGM_GameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void AGM_GameModeBase::OnGameOver_Implementation(bool bSuccess)
{
}

void AGM_GameModeBase::FinishGame(bool bSuccess)
{
	HmGameState = bSuccess ? EGM_GameState::Won : EGM_GameState::Lost;
	GameOverDelegate.Broadcast(bSuccess);
}

