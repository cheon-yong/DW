// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/StageComponent.h"
#include "Game/DWStageData.h"

UStageComponent::UStageComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}



void UStageComponent::InitializeComponent()
{
	Super::InitializeComponent();

}

void UStageComponent::BeginPlay()
{
	Super::BeginPlay();

	ReadyStage();
}

void UStageComponent::ReadyStage()
{
	LoadStageData();

	CurrentStageData->Ready();
}

void UStageComponent::PlayingStage()
{
	
	CurrentStageData->Playing();
}

void UStageComponent::CompleteStage()
{
	
	CurrentStageData->Complete();
}

void UStageComponent::FailStage()
{

	CurrentStageData->Fail();
}

void UStageComponent::LoadStageData()
{
	auto& StageDatas = DWStageData->StageDatas;
	if (CurrentStageIndex + 1 >= StageDatas.Num())
	{
		// TODO : Error Check?
		return;
	}

	UStageData* PrevData = CurrentStageData;
	if (PrevData != nullptr)
	{
		PrevData->Clear();
	}
	CurrentStageIndex++;
	CurrentStageData = NewObject<UStageData>(this, StageDatas[CurrentStageIndex]);
	OnStageChanged.Broadcast(CurrentStageData, PrevData);
}