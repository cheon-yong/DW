// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"

#include "QuestReportComponent.generated.h"

class UQuestCategory;
class UQuestTaskTarget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DW_API UQuestReportComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UQuestReportComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void Report();

public:	


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Quest)
	TSubclassOf<UQuestCategory> QuestCategoryClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Quest)
	TObjectPtr<UQuestCategory> QuestCategory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Quest)
	bool bSelfTarget = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Quest, meta=(EditCondition="bSelfTarget"))
	TSubclassOf<UObject> TaskTarget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Quest)
	int32 SuccessCount = 1;
};
