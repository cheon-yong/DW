// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/QuestDefinition.h"
#include "Quest/QuestTaskTarget.h"
#include "Quest/QuestReward.h"
#include "Quest/QuestTask.h"

void UQuestDefinition::Setup()
{
	// Create Instances
	for (TSubclassOf<UQuestTask> Task : QuestTaskClass)
	{
		UQuestTask* QuestTask = NewObject<UQuestTask>(this, Task);
		QuestTasks.Add(QuestTask);
	}

	for (UQuestTask* QuestTask : QuestTasks)
	{
		QuestTask->Setup(this);
		QuestTask->OnSuccessChanged.AddUObject(this, &ThisClass::OnSuccessChanged);
	}

	QuestState = EQuestState::Running;
	QuestTasks[CurrentIndex]->Start();
}

void UQuestDefinition::ReceiveReport(TSubclassOf<UQuestCategory> CategoryClass, UObject* TaskTarget, int32 SuccessCount)
{
	if (QuestState != EQuestState::Running)
	{
		return;
	}

	QuestTasks[CurrentIndex]->ReceiveReport(CategoryClass, TaskTarget, SuccessCount);

	
}

void UQuestDefinition::OnSuccessChanged(UQuestTask* Task, int32 CurrentSuccess, int32 PrevSuccess)
{
}
