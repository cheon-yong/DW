// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "QuestTaskAction.generated.h"

class UQuestTask;

/**
 * 
 */


UCLASS(DefaultToInstanced, EditInlineNew, Abstract)
class DW_API UQuestTaskAction : public UObject
{
	GENERATED_BODY()
	
public:
	virtual int32 Run(UQuestTask* Task, int32 CurrentCount, int32 SuccessCount) PURE_VIRTUAL(UQuestTaskAction::Run, return 0;);
};
