// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Subsystems/GameInstanceSubsystem.h"
#include "GameplayTagContainer.h"

#include "QuestManagerSubsystem.generated.h"

class UQuestCategory;
class UQuestInstance;
class UQuestDefinition;
class UQuestTaskTarget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestSystemEvent, UQuestDefinition*, Quest);

/**
 * 
 */
UCLASS()
class DW_API UQuestManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	void RegisterQuest(TSubclassOf<UQuestDefinition> InQuestDefinition);

	void ReceiveReport(TSubclassOf<UQuestCategory> CategoryClass, UObject* TaskTarget, int32 SuccessCount);

protected:
	UFUNCTION()
	void OnQuestCompleted(UQuestDefinition* InQuestDefinition);

	UFUNCTION()
	void OnQuestCanceled(UQuestDefinition* InQuestDefinition);

public:
	UPROPERTY(BlueprintAssignable)
	FOnQuestSystemEvent OnQuestRegister;

	UPROPERTY(BlueprintAssignable)
	FOnQuestSystemEvent OnQuestComplete;

	UPROPERTY(BlueprintAssignable)
	FOnQuestSystemEvent OnQuestCancel;

public:

	UPROPERTY(VisibleAnywhere)
	TArray<TWeakObjectPtr<UQuestDefinition>> Quests;
};
