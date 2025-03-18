// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/DWStageSubsystem.h"

#include "Game/DWStageData.h"
#include <Kismet/GameplayStatics.h>


UDWStageSubsystem::UDWStageSubsystem()
{

}

void UDWStageSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	LoadDefaultStageData();

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

UE_DISABLE_OPTIMIZATION
void UDWStageSubsystem::LoadStage(TSubclassOf<UStageData> NewStageData)
{
	// 미리 선언된 데이터가 아니라면 반환
	if (DWStageData->StageDatas.Find(NewStageData) == INDEX_NONE)
		return;

	CurrentStageData = NewObject<UStageData>(this, NewStageData);
	
	FName DestinationLevel = CurrentStageData->StageName;
	FLatentActionInfo LatentActionInfo;
	LatentActionInfo.CallbackTarget = this;
	LatentActionInfo.ExecutionFunction = FName(TEXT("OnStreamLevelLoaded"));

	UGameplayStatics::LoadStreamLevel(this, DestinationLevel, true, false, LatentActionInfo);
}
UE_ENABLE_OPTIMIZATION

void UDWStageSubsystem::ReadyStage()
{

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

void UDWStageSubsystem::LoadNextStageData()
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

void UDWStageSubsystem::OnStreamLevelLoaded()
{
	FTimerHandle WaitHandle;
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			UGameplayStatics::UnloadStreamLevel(this, "StartMap", FLatentActionInfo(), false);
		}), 0.2f, false);
}