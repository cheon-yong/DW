// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"

#include "QuestTask.generated.h"

class UQuestDefinition;
class UQuestTaskTarget;
class UQuestTaskAction;

UENUM(BlueprintType)
enum class ETaskState : uint8
{
	Inactive,
	Running,
	Complete,
};



DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSuccessChanged, UQuestTask*/* Task */, int32/* CurrentSuccess*/, int32/*PrevSuccess*/);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnStateChanged, UQuestTask*/* Task */, ETaskState/* CurrentState */, ETaskState/*PrevState*/);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class DW_API UQuestTask : public UObject
{
	GENERATED_BODY()
	
public:
	void Setup(UQuestDefinition* InQuest);

	void Start();

	void End();

	void ReceiveReport(FGameplayTag CategoryTag, UQuestTaskTarget* TaskTarget, int32 SuccessCount);

	void SetSuccessCount(int32 SuccessCount);

	void SetTaskState(ETaskState NewState);
	
	bool IsTarget(FGameplayTag InCategoryTag, UQuestTaskTarget* InTaskTarget);

public:
	FOnSuccessChanged OnSuccessChanged;
	FOnStateChanged OnStateChanged;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UQuestDefinition> Quest;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Quest, meta = (Categories = Quest))
	FGameplayTag QuestCategory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Quest)
	TObjectPtr<UQuestTaskAction> TaskAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Quest)
	TArray<TObjectPtr<UQuestTaskTarget>> TaskTargets;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Quest)
	ETaskState TaskState = ETaskState::Inactive;

	int32 CurrentCount = 0;
};
