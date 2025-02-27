// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/GameStateComponent.h"
#include "MonsterSpawnComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMonsterChanged, int32, MonsterNum);

class ADWMonsterSpawnPoint;
class USpawnMonsterData;
class ADWCharacterNonPlayer;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class DW_API UMonsterSpawnComponent : public UGameStateComponent
{
	GENERATED_BODY()
	
public:

	UMonsterSpawnComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnGameStateChange(FGameplayTag NewStateTag);

protected:
	void FindAllSpawnPoints();

	void StartSpawnMonster();

	void StopSpawnMonster();

	UFUNCTION()
	void SpawnMonster(TSubclassOf<ADWCharacterNonPlayer> MonsterToSpawn);

public:
	UPROPERTY(BlueprintAssignable)
	FOnMonsterChanged OnMonsterChanged;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Data)
	TObjectPtr<USpawnMonsterData> SpawnMonsterData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
	TSet<TObjectPtr<ADWCharacterNonPlayer>> Monsters;

	TMap<FTimerHandle, FTimerDelegate> TimerDelegates;

	TArray<TObjectPtr<ADWMonsterSpawnPoint>> SpawnPoints;
};
