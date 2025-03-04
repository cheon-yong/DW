// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Tag/DWGameplayTag.h"
#include "Game/SpawnMonsterData.h"
#include "GameFramework/GameMode.h"
#include "DWGameMode.generated.h"

class UDWStageData;
struct FStageData;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameStateChanged, FGameplayTag, StateTag);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChanged, int32, NewScore);

UCLASS(minimalapi)
class ADWGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ADWGameMode();

	void OnPlayerDead();

	const FStageData& GetCurrentStageData();

	UFUNCTION(BlueprintCallable)
	void SetScore(int32 NewScore);
		
	UFUNCTION(BlueprintCallable)
	int32 GetScore() { return Score; }

	UFUNCTION(BlueprintCallable)
	void SetGameStateTag(FGameplayTag NewStateTag);

	void GameOver();

	void CheckClear();



	//~ Begin AGameModeBase Interface
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void StartPlay() override;
	//~ End AGameModeBase Interface
protected:
	

public:
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, Category = State);
	FOnGameStateChanged OnGameStateChanged;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, Category = State);
	FOnScoreChanged OnScoreChanged;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Stage)
	TObjectPtr<UDWStageData> DWStageData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayTag GameStateTag;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 CurrentStageIndex = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 Score = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 ClearScore = 0;
};



