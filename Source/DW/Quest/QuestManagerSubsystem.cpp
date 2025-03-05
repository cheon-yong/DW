// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/QuestManagerSubsystem.h"
#include "Quest/QuestDefinition.h"
#include "Quest/QuestTaskTarget.h"

void UQuestManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
}

void UQuestManagerSubsystem::RegisterQuest(TSubclassOf<UQuestDefinition> InQuestDefinition)
{
	UQuestDefinition* Quest = NewObject<UQuestDefinition>(this, InQuestDefinition);

	Quest->OnCompleted.AddDynamic(this, &ThisClass::OnQuestCompleted);
	Quest->OnCanceled.AddDynamic(this, &ThisClass::OnQuestCanceled);

	Quests.Emplace(Quest);

	Quest->Setup();
	OnQuestRegistered.Broadcast(Quest);
}

void UQuestManagerSubsystem::ReceiveReport(TSubclassOf<UQuestCategory> CategoryClass, UObject* TaskTarget, int32 SuccessCount)
{
	for (UQuestDefinition* Quest : Quests)
	{
		Quest->ReceiveReport(CategoryClass, TaskTarget, SuccessCount);
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

