// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Subsystems/GameInstanceSubsystem.h"
#include "GameplayTagContainer.h"

#include "QuestManagerSubsystem.generated.h"

class UQuestInstance;
class UQuestDefinition;
class UQuestTaskTarget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestRegistered, UQuestDefinition*, Quest);

/**
 * 
 */
UCLASS()
class DW_API UQuestManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	void RegisterQuest(UQuestDefinition* InQuestDefinition);

	void ReceiveReport(FGameplayTag CategoryTag, UQuestTaskTarget* TaskTarget, int32 SuccessCount);

	UPROPERTY(BlueprintAssignable)
	FOnQuestRegistered OnQuestRegistered;

protected:
	UFUNCTION()
	void OnQuestCompleted(UQuestDefinition* InQuestDefinition);

	UFUNCTION()
	void OnQuestCanceled(UQuestDefinition* InQuestDefinition);

protected:
	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<UQuestDefinition>> Quests;
};
