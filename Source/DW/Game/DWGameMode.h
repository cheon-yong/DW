// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Tag/DWGameplayTag.h"
#include "Game/SpawnMonsterData.h"
#include "GameFramework/GameMode.h"
#include "DWGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameStateChanged, FGameplayTag, StateTag);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChanged, int32, NewScore);

UCLASS(minimalapi)
class ADWGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ADWGameMode();

	void OnPlayerDead();

	UFUNCTION(BlueprintCallable)
	void SetScore(int32 NewScore);
		
	UFUNCTION(BlueprintCallable)
	int32 GetScore() { return Score; }

	UFUNCTION(BlueprintCallable)
	void SetGameStateTag(FGameplayTag NewStateTag);

	void GameOver();

	void CheckClear();

protected:

public:
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, Category = State);
	FOnGameStateChanged OnGameStateChanged;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, Category = State);
	FOnScoreChanged OnScoreChanged;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayTag GameStateTag;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 Score = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 ClearScore = 3;
};



