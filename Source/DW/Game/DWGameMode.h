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

UCLASS(minimalapi)
class ADWGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ADWGameMode();

	void OnPlayerDead();

	UFUNCTION(BlueprintCallable)
	void SetGameStateTag(FGameplayTag NewStateTag);

	void GameOver();

	//~ Begin AGameModeBase Interface
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void StartPlay() override;
	virtual void BeginPlay() override;
	//~ End AGameModeBase Interface
protected:
	

public:
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, Category = State);
	FOnGameStateChanged OnGameStateChanged;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Stage)
	TObjectPtr<UDWStageData> DWStageData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayTag GameStateTag;

};



