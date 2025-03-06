// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "QuestGiverComponent.generated.h"

class UQuestDefinition;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DW_API UQuestGiverComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UQuestGiverComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable)
	void GiveQuest();

	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Quest)
	TSubclassOf<UQuestDefinition> QuestToGive;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Quest)
	bool bAlreadyGive = false;
};
