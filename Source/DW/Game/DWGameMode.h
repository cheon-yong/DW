// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Tag/DWGameplayTag.h"
#include "Game/SpawnMonsterData.h"
#include "GameFramework/GameMode.h"
#include "DWGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameStateChanged, FGameplayTag, StateTag);



UCLASS(minimalapi)
class ADWGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ADWGameMode();

	UFUNCTION(BlueprintCallable)
	void SetGameStateTag(FGameplayTag NewStateTag);

protected:

public:
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, Category = State);
	FOnGameStateChanged OnGameStateChanged;

protected:

	FGameplayTag GameStateTag;


};



