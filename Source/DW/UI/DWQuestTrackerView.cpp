// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DWQuestTrackerView.h"

#include "Components/VerticalBox.h"
#include "Quest/QuestManagerSubsystem.h"
#include "UI/DWQuestTracker.h"

void UDWQuestTrackerView::NativeConstruct()
{
	Super::NativeConstruct();

	if (UQuestManagerSubsystem* QuestManager = GetGameInstance()->GetSubsystem<UQuestManagerSubsystem>())
	{
		QuestManager->OnQuestRegister.AddDynamic(this, &ThisClass::CreateQuestTracker);

		for (TWeakObjectPtr<UQuestDefinition> Quest : QuestManager->Quests)
		{
			CreateQuestTracker(Quest.Get());
		}
	}
}

void UDWQuestTrackerView::CreateQuestTracker(UQuestDefinition* QuestDefinition)
{
	K2_CreateQuestTracker(QuestDefinition);
}
