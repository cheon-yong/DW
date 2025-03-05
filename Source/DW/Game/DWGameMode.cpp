// Copyright Epic Games, Inc. All Rights Reserved.

#include "DWGameMode.h"
#include "Character/DWCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Tag/DWGameplayTag.h"
#include "Game/SpawnMonsterData.h"
#include "Game/DWStageData.h"
#include "Game/DWGameState.h"
#include "Game/MonsterSpawnComponent.h"

ADWGameMode::ADWGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	GameStateTag = DWTAG_GAME_STATE_READY;
}

void ADWGameMode::OnPlayerDead()
{
	GameOver();
}

void ADWGameMode::SetGameStateTag(FGameplayTag NewStateTag)
{
	if (GameStateTag.MatchesTagExact(NewStateTag))
		return;

	GameStateTag = NewStateTag;
	OnGameStateChanged.Broadcast(NewStateTag);
}

void ADWGameMode::GameOver()
{
	SetGameStateTag(DWTAG_GAME_STATE_DEFEATED);
}

void ADWGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void ADWGameMode::StartPlay()
{
	Super::StartPlay();
}

void ADWGameMode::BeginPlay()
{
	Super::BeginPlay();
}
