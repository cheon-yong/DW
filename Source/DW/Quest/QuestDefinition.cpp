// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/QuestDefinition.h"
#include "Quest/QuestTaskTarget.h"
#include "Quest/QuestReward.h"
#include "Quest/QuestTask.h"

void UQuestDefinition::Setup()
{
	for (UQuestTask* Task : QuestTasks)
	{
		Task->Setup(this);
		Task->OnSuccessChanged.AddUObject(this, &ThisClass::OnSuccessChanged);
	}

	QuestState = EQuestState::Running;
	QuestTasks[CurrentIndex]->Start();
}

void UQuestDefinition::ReceiveReport(FGameplayTag CategoryTag, UQuestTaskTarget* TaskTarget, int32 SuccessCount)
{
}

void UQuestDefinition::OnSuccessChanged(UQuestTask* Task, int32 CurrentSuccess, int32 PrevSuccess)
{
}
