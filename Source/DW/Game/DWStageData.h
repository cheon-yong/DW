// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DWStageData.generated.h"

class USpawnMonsterData;
class UQuestDefinition;

USTRUCT(Blueprintable)
struct FStageData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName StageName;
		
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USpawnMonsterData> MonsterData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Quest)
	TArray<TSubclassOf<UQuestDefinition>> Quests;
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
	TArray<FStageData> StageDatas;
};
