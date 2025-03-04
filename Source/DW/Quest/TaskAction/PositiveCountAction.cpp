// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/TaskAction/PositiveCountAction.h"

int32 UPositiveCountAction::Run(UQuestTask* Task, int32 CurrentCount, int32 SuccessCount)
{
	return SuccessCount > 0 ? CurrentCount + SuccessCount : CurrentCount;
}
