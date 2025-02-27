// Copyright Epic Games, Inc. All Rights Reserved.

#include "DWGameMode.h"
#include "Character/DWCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Tag/DWGameplayTag.h"
#include "Game/SpawnMonsterData.h"

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

void ADWGameMode::SetGameStateTag(FGameplayTag NewStateTag)
{
	GameStateTag = NewStateTag;
	OnGameStateChanged.Broadcast(NewStateTag);
}