// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"

#include "QuestDefinition.generated.h"

class UQuestTask;
class UQuestReward;
class UQuestTaskTarget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestEvent, UQuestDefinition*, Quest);

UENUM(BlueprintType)
enum class EQuestState : uint8
{
	Inactive,
	Running,
	Complete,
	Cancel,
	WaitingForCompletion
};

/**
 * 
 */
UCLASS(Blueprintable, Const)
class DW_API UQuestDefinition : public UObject
{
	GENERATED_BODY()
	
public:
	void Setup();

	void ReceiveReport(FGameplayTag CategoryTag, UQuestTaskTarget* TaskTarget, int32 SuccessCount);

protected:
	void OnSuccessChanged(UQuestTask* Task, int32 CurrentSuccess, int32 PrevSuccess);

public:
	UPROPERTY(BlueprintAssignable)
	FOnQuestEvent OnCompleted;

	UPROPERTY(BlueprintAssignable)
	FOnQuestEvent OnCanceled;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Quest, meta=(Categories=Quest))
	FGameplayTag QuestCategory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Quest)
	FName QuestName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Quest)
	FString QuestDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Quest)
	TArray<TSubclassOf<UQuestTask>> QuestTaskClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Quest)
	TArray<TObjectPtr<UQuestTask>> QuestTasks;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Quest)
	TArray<TSubclassOf<UQuestReward>> QuestRewards;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Quest)
	EQuestState QuestState = EQuestState::Inactive;

	int32 CurrentIndex = 0;
};
