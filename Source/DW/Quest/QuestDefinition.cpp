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
		QuestTask->OnSuccessChanged.AddDynamic(this, &ThisClass::OnSuccessChanged);
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

	if (QuestTasks[CurrentIndex]->IsComplete())
	{
		if (CurrentIndex + 1 == QuestTasks.Num())
		{
			QuestTasks[CurrentIndex]->End();
			SetQuestState(EQuestState::WaitingForCompletion);
			if (bAutoComplete)
				Complete();
		}
		else
		{
			auto PrevTask = QuestTasks[CurrentIndex++];
			PrevTask->End();
			auto CurrentTask = QuestTasks[CurrentIndex];
			CurrentTask->Start();
			OnTaskChanged.Broadcast(this, PrevTask, CurrentTask);
		}
	}
	

}

void UQuestDefinition::SetQuestState(EQuestState NewState)
{
	if (QuestState == NewState)
		return;

	auto PrevState = QuestState;
	QuestState = NewState;
	OnQuestStateChanged.Broadcast(this, QuestState, PrevState);
}

void UQuestDefinition::Complete()
{
	CheckIsRunning();

	SetQuestState(EQuestState::Complete);

	// TODO : Reward
	for (TSubclassOf<UQuestReward> RewardClass : QuestRewards)
	{
		UQuestReward* Reward = NewObject<UQuestReward>(this, RewardClass);
		Reward->Give();
	}
	
	OnCompleted.Broadcast(this);

	OnQuestStateChanged.Clear();
	OnTaskChanged.Clear();
	OnCompleted.Clear();
	OnCanceled.Clear();
	OnTaskSuccessChanged.Clear();
}

void UQuestDefinition::CheckIsRunning()
{
	check(QuestState != EQuestState::Inactive);
	check(QuestState != EQuestState::Complete);
	check(QuestState != EQuestState::Cancel);
}

void UQuestDefinition::OnSuccessChanged(UQuestTask* Task, int32 CurrentSuccess, int32 PrevSuccess)
{
	OnTaskSuccessChanged.Broadcast(this, Task, CurrentSuccess, PrevSuccess);
}
