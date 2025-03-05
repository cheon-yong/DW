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

	LoadStageData();
}

void UStageComponent::BeginPlay()
{
	Super::BeginPlay();

	SetStageState(EStageState::Ready);
}

void UStageComponent::LoadStageData()
{
	auto& StageDatas = DWStageData->StageDatas;
	if (CurrentStageIndex >= StageDatas.Num())
	{
		// TODO : Error Check?
		return;
	}

	CurrentStageData = StageDatas[CurrentStageIndex++];

	OnStageChanged.Broadcast(CurrentStageData);
}

void UStageComponent::SetStageState(EStageState NewState)
{
	if (StageState == NewState)
		return;

	StageState = NewState;
	OnStageStateChanged.Broadcast(StageState);
}
