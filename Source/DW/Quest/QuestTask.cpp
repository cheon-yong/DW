// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/QuestTask.h"
#include "Quest/QuestTaskAction.h"
#include "Quest/QuestTaskTarget.h"

void UQuestTask::Setup(UQuestDefinition* InQuest)
{
	Quest = InQuest;
}

void UQuestTask::Start()
{
	SetTaskState(ETaskState::Running);
}

void UQuestTask::End()
{
	OnStateChanged.Clear();
	OnSuccessChanged.Clear();
}

void UQuestTask::ReceiveReport(FGameplayTag CategoryTag, UQuestTaskTarget* TaskTarget, int32 SuccessCount)
{
	if (IsTarget(CategoryTag, TaskTarget))
	{
		SetSuccessCount(SuccessCount);
	}
}

void UQuestTask::SetSuccessCount(int32 SuccessCount)
{
	int32 NewCount = TaskAction->Run(this, CurrentCount, SuccessCount);
}

void UQuestTask::SetTaskState(ETaskState NewState)
{
	auto PrevState = TaskState;
	TaskState = NewState;

	OnStateChanged.Broadcast(this, TaskState, PrevState);
}

bool UQuestTask::IsTarget(FGameplayTag InCategoryTag, UQuestTaskTarget* InTaskTarget)
{
	bool IsSameCategory = QuestCategory.MatchesTagExact(InCategoryTag);
	if (IsSameCategory == false)
	{
		return false;
	}
		
	bool IsTarget = true;
	for (UQuestTaskTarget* TaskTarget : TaskTargets)
	{
		if (!TaskTarget->IsEqual(InTaskTarget))
		{
			IsTarget = false;
			break;
		}
	}

	if (IsTarget == false)
	{
		return false;
	}
	
	return true;
}
