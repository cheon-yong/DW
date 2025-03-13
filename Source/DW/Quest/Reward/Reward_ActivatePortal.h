// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Quest/QuestReward.h"
#include "Reward_ActivatePortal.generated.h"

/**
 * 
 */
UCLASS()
class DW_API UReward_ActivatePortal : public UQuestReward
{
	GENERATED_BODY()
	
public:
	virtual void Give() override;

};
