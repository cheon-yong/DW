// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/QuestTask.h"
#include "Quest/Category/QuestCategory.h"
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

void UQuestTask::ReceiveReport(TSubclassOf<UQuestCategory> CategoryClass, UObject* TaskTarget, int32 SuccessCount)
{
	if (IsTarget(CategoryClass, TaskTarget))
	{
		SetSuccessCount(SuccessCount);
	}
}

void UQuestTask::SetSuccessCount(int32 SuccessCount)
{
	int32 NewCount = TaskAction.GetDefaultObject()->Run(this, CurrentCount, SuccessCount);
}

void UQuestTask::SetTaskState(ETaskState NewState)
{
	auto PrevState = TaskState;
	TaskState = NewState;

	OnStateChanged.Broadcast(this, TaskState, PrevState);
}

bool UQuestTask::IsTarget(TSubclassOf<UQuestCategory> InCategory, UObject* InTaskTarget)
{
	//bool IsSameCategory = QuestCategory.MatchesTagExact(InCategoryTag);

	
	bool IsSameCategory = true;
	if (IsSameCategory == false)
	{
		return false;
	}
		
	bool IsTarget = true;
	for (UObject* TaskTarget : TaskTargets)
	{
		/*if (!TaskTarget->IsEqual(InTaskTarget))
		{
			IsTarget = false;
			break;
		}*/
	}

	if (IsTarget == false)
	{
		return false;
	}
	
	return true;
}
