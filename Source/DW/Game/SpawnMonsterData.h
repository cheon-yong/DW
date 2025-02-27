// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SpawnMonsterData.generated.h"

class ADWCharacterNonPlayer;

USTRUCT(BlueprintType)
struct FSpawnData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ADWCharacterNonPlayer> Monster;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnInterval = 0;
};

/**
 * 
 */
UCLASS()
class DW_API USpawnMonsterData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSpawnData> SpawnDatas;
};
