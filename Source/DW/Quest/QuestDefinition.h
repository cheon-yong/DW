// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"

#include "QuestDefinition.generated.h"

class UQuestCategory;
class UQuestTask;
class UQuestReward;
class UQuestTaskTarget;

UENUM(BlueprintType)
enum class EQuestState : uint8
{
	Inactive,
	Running,
	Complete,
	Cancel,
	WaitingForCompletion
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestEvent, UQuestDefinition*, Quest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnQuestStateChanged, UQuestDefinition*, Quest, EQuestState, CurrentState, EQuestState, PrevState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnTaskChanged, UQuestDefinition*, Quest, UQuestTask*, CurrentTask, UQuestTask*, PrevTask);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnTaskSuccessChanged, UQuestDefinition*, Quest, UQuestTask*, Task, int32, CurrentCount, int32, PrevCount);

/**
 * 
 */
UCLASS(Blueprintable, Const)
class DW_API UQuestDefinition : public UObject
{
	GENERATED_BODY()
	
public:
	void Setup();

	void ReceiveReport(TSubclassOf<UQuestCategory> CategoryClass, UObject* TaskTarget, int32 SuccessCount);

	void SetQuestState(EQuestState NewState);

	void Complete();

	void CheckIsRunning();

protected:
	UFUNCTION()
	void OnSuccessChanged(UQuestTask* Task, int32 CurrentSuccess, int32 PrevSuccess);

public:
	UPROPERTY(BlueprintAssignable)
	FOnQuestStateChanged OnQuestStateChanged;

	UPROPERTY(BlueprintAssignable)
	FOnTaskSuccessChanged OnTaskSuccessChanged;

	UPROPERTY(BlueprintAssignable)
	FOnTaskChanged OnTaskChanged;

	UPROPERTY(BlueprintAssignable)
	FOnQuestEvent OnCompleted;

	UPROPERTY(BlueprintAssignable)
	FOnQuestEvent OnCanceled;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Quest, meta=(Categories=Quest))
	TSubclassOf<UQuestCategory> QuestCategory;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Option)
	bool bAutoComplete = false;

	int32 CurrentIndex = 0;
};
