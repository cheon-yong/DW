// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DWQuestTracker.generated.h"

class UTextBlock;
class UQuestDefinition;
/**
 * 
 */
UCLASS()
class DW_API UDWQuestTracker : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Setup(UQuestDefinition* QuestDefinition);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetQuestText();

	UFUNCTION()
	void UpdateTask(UQuestDefinition* Quest, UQuestTask* CurrentTask, UQuestTask* PrevTask);
	
	UFUNCTION()
	void OnQuestComplete(UQuestDefinition* Quest);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UUserWidget> TaskDescriptionClass;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> QuestText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText NameFormatText;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UQuestDefinition> TargetQuest;
};
