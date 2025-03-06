// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuestReward.generated.h"

/**
 * 
 */
UCLASS(DefaultToInstanced, EditInlineNew, Abstract)
class DW_API UQuestReward : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void Give() PURE_VIRTUAL(UQuestReward::Give, return ;);
};
