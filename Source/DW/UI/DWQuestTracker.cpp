// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DWQuestTracker.h"

#include "Quest/QuestDefinition.h"
#include "Quest/QuestTask.h"
#include "Components/TextBlock.h"

void UDWQuestTracker::Setup(UQuestDefinition* QuestDefinition)
{
	TargetQuest = QuestDefinition;

	SetQuestText();

	TargetQuest->OnTaskChanged.AddDynamic(this, &ThisClass::UpdateTask);
	TargetQuest->OnCompleted.AddDynamic(this, &ThisClass::OnQuestComplete);

	for (UQuestTask* Task : TargetQuest->QuestTasks)
	{

	}
}

void UDWQuestTracker::UpdateTask(UQuestDefinition* Quest, UQuestTask* CurrentTask, UQuestTask* PrevTask)
{
	//K2_UpdateTask(Quest, CurrentTask, PrevTask);
}

void UDWQuestTracker::OnQuestComplete(UQuestDefinition* Quest)
{
	//K2_OnQuestComplete(Quest);
}
