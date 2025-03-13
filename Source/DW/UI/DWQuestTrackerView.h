// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "Quest/QuestDefinition.h"
#include "DWQuestTrackerView.generated.h"

class UQuestDefinition;
class UVerticalBox;

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class DW_API UDWQuestTrackerView : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void CreateQuestTracker(UQuestDefinition* QuestDefinition);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Quest, meta = (DisplayName = "CreateQuestTracker"))
	void K2_CreateQuestTracker(const UQuestDefinition* QuestDefinition);
		
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	TObjectPtr<UVerticalBox> VerticalBox;
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> QuestTrackerClass;
};
