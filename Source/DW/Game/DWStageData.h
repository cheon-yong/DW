// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DWStageData.generated.h"


UENUM(BlueprintType)
enum class EStageState : uint8
{
	Ready,
	Playing,
	Complete,
	Fail,
};

class USpawnMonsterData;
class UQuestDefinition;


DECLARE_MULTICAST_DELEGATE_OneParam(FOnStageStateChanged, UStageData*);

UCLASS(Blueprintable)
class UStageData : public UObject
{
	GENERATED_BODY()

public:
	void Ready();
	void Playing();
	void Fail();
	void Complete();
	void Clear();
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName StageName;
		
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USpawnMonsterData> MonsterData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Quest)
	TArray<TSubclassOf<UQuestDefinition>> Quests;

	EStageState StageState = EStageState::Ready;

	FOnStageStateChanged OnReady;

	FOnStageStateChanged OnPlaying;

	FOnStageStateChanged OnFail;

	FOnStageStateChanged OnComplete;
	
};

/**
 * 
 */
UCLASS()
class DW_API UDWStageData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stage)
	TArray<TSubclassOf<UStageData>> StageDatas;
};
