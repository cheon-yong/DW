// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/QuestManagerSubsystem.h"
#include "Quest/QuestDefinition.h"
#include "Quest/QuestTaskTarget.h"

void UQuestManagerSubsystem::RegisterQuest(UQuestDefinition* InQuestDefinition)
{
	InQuestDefinition->OnCompleted.AddDynamic(this, &ThisClass::OnQuestCompleted);
	InQuestDefinition->OnCanceled.AddDynamic(this, &ThisClass::OnQuestCanceled);

	Quests.Emplace(InQuestDefinition);

	InQuestDefinition->Setup();
	OnQuestRegistered.Broadcast(InQuestDefinition);
}

void UQuestManagerSubsystem::ReceiveReport(FGameplayTag CategoryTag, UQuestTaskTarget* TaskTarget, int32 SuccessCount)
{
	for (UQuestDefinition* Quest : Quests)
	{
		Quest->ReceiveReport(CategoryTag, TaskTarget, SuccessCount);
	}
}

void UQuestManagerSubsystem::OnQuestCompleted(UQuestDefinition* InQuestDefinition)
{
	Quests.Remove(InQuestDefinition);
}

void UQuestManagerSubsystem::OnQuestCanceled(UQuestDefinition* InQuestDefinition)
{
	Quests.Remove(InQuestDefinition);
}

