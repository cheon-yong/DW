// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"

#include "QuestCategory.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnTaskSuccessed);

/**
 * 
 */
UCLASS(Blueprintable, Const, Abstract)
class DW_API UQuestCategory : public UObject
{
	GENERATED_BODY()
	
public:
	void Init(AActor* InOwner);

	virtual void Bind() PURE_VIRTUAL(UQuestCategory::Bind(), ;);

public:
	FOnTaskSuccessed OnTaskSuccessed;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Quest, meta = (Categories = Quest))
	FGameplayTag CategoryTag;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AActor* Owner;
};
