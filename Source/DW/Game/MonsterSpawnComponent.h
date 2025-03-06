// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/GameStateComponent.h"
#include "Game/StageComponent.h"

#include "MonsterSpawnComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMonsterChanged, int32, MonsterNum);

class ADWMonsterSpawnPoint;
class USpawnMonsterData;
class ADWCharacterNonPlayer;
struct FGameplayEffectSpec;
class UStageData;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class DW_API UMonsterSpawnComponent : public UGameStateComponent
{
	GENERATED_BODY()
	
public:
	UMonsterSpawnComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void InitializeComponent() override;
	virtual void BeginPlay() override;

	void OnStageChanged(UStageData* CurrentStageData, UStageData* PrevStageData);

	void OnStageReady(UStageData* CurrentStageData);

	void OnStagePlaying(UStageData* CurrentStageData);

	void OnStageComplete(UStageData* CurrentStageData);

	void OnStageFail(UStageData* CurrentStageData);

	void SetSpawnMonsterData(USpawnMonsterData* InSpawnMonsterData);

protected:
	void FindAllSpawnPoints();

	void StartSpawnMonster();

	void StopAllAI();

	void OnMonsterDead(AActor* Target, AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue);

	void StopSpawnMonster();

	UFUNCTION()
	void DestroyMonster(ADWCharacterNonPlayer* Monster);

	UFUNCTION()
	void SpawnMonster(TSubclassOf<ADWCharacterNonPlayer> MonsterToSpawn);

public:
	UPROPERTY(BlueprintAssignable)
	FOnMonsterChanged OnMonsterChanged;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
	TObjectPtr<USpawnMonsterData> SpawnMonsterData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
	TSet<TObjectPtr<ADWCharacterNonPlayer>> Monsters;

	TMap<FTimerHandle, FTimerDelegate> TimerDelegates;
	
	TArray<TObjectPtr<ADWMonsterSpawnPoint>> SpawnPoints;

	FTimerHandle CurrentTimerHandle;
};
