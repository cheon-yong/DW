// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/QuestGiverComponent.h"

#include "Quest/QuestDefinition.h"
#include "Quest/QuestManagerSubsystem.h"

// Sets default values for this component's properties
UQuestGiverComponent::UQuestGiverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UQuestGiverComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UQuestGiverComponent::GiveQuest()
{
	if (bAlreadyGive)
		return;

	bAlreadyGive = true;

	if (UGameInstance* GameInstance = GetWorld()->GetGameInstance())
	{
		if (UQuestManagerSubsystem* QuestSubsystem = GameInstance->GetSubsystem<UQuestManagerSubsystem>())
		{
			if (QuestToGive != nullptr)
				QuestSubsystem->RegisterQuest(QuestToGive);
		}
	}
}

