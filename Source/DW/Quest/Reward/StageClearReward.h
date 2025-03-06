// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Quest/QuestReward.h"
#include "StageClearReward.generated.h"

/**
 * 
 */
UCLASS()
class DW_API UStageClearReward : public UQuestReward
{
	GENERATED_BODY()
	
public:
	virtual void Give() override;
	
};
