// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/QuestReportComponent.h"
#include "Quest/QuestManagerSubsystem.h"
#include "Quest/Category/QuestCategory.h"

// Sets default values for this component's properties
UQuestReportComponent::UQuestReportComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UQuestReportComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	QuestCategory = NewObject<UQuestCategory>(this, QuestCategoryClass);

	if (AActor* OutActor = Cast<AActor>(GetOuter()))
	{
		QuestCategory->Init(OutActor);
		QuestCategory->OnTaskSuccessed.AddUObject(this, &ThisClass::Report);
		QuestCategory->Bind();
	}
}

void UQuestReportComponent::Report()
{
	if (UGameInstance* GameInstance = GetWorld()->GetGameInstance())
	{
		if (UQuestManagerSubsystem* QuestSubsystem = GameInstance->GetSubsystem<UQuestManagerSubsystem>())
		{
			UObject* Target = bSelfTarget ? GetOuter() : TaskTarget.GetDefaultObject();
			QuestSubsystem->ReceiveReport(QuestCategoryClass, Target, SuccessCount);
		}
	}	
}