// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Quest/QuestTaskAction.h"
#include "PositiveCountAction.generated.h"

class UQuestTask;
/**
 * 
 */
UCLASS()
class DW_API UPositiveCountAction : public UQuestTaskAction
{
	GENERATED_BODY()
	
public:
	virtual int32 Run(UQuestTask* Task, int32 CurrentCount, int32 SuccessCount) override;
};
