// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/DWStageSubsystem.h"

#include "Game/DWStageData.h"

UDWStageSubsystem::UDWStageSubsystem()
{

}



void UDWStageSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	LoadDefaultStageData();

	ReadyStage();
}


void UDWStageSubsystem::LoadDefaultStageData()
{
	if (!DWStageData && !DefaultStageDataClass.IsNull())
	{
		TSubclassOf<UDWStageData> DWStageClass = DefaultStageDataClass.LoadSynchronous();
		DWStageData = NewObject<UDWStageData>(this, DWStageClass);
	}
}

void UDWStageSubsystem::Deinitialize()
{
	Super::Deinitialize();

	if (CurrentStageData != nullptr)
	{
		CurrentStageData->Clear();
	}
}

void UDWStageSubsystem::ReadyStage()
{
	LoadStageData();

	CurrentStageData->Ready();
}

void UDWStageSubsystem::PlayingStage()
{

	CurrentStageData->Playing();
}

void UDWStageSubsystem::CompleteStage()
{

	CurrentStageData->Complete();
}

void UDWStageSubsystem::FailStage()
{

	CurrentStageData->Fail();
}

void UDWStageSubsystem::LoadStageData()
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