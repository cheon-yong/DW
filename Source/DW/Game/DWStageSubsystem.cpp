// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/DWStageSubsystem.h"

#include "Game/DWStageData.h"
#include "Kismet/GameplayStatics.h"
#include "WorldPartition/DataLayer/DataLayerManager.h"


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

	BeforeStageData = CurrentStageData;

	CurrentStageData = NewObject<UStageData>(this, NewStageData);

	// Data Layer Load
	TSoftObjectPtr<UDataLayerAsset> DataLayer = CurrentStageData->StageDataLayer;
	UDataLayerManager* DataLayerManager = UDataLayerManager::GetDataLayerManager(GetWorld());
	DataLayerManager->SetDataLayerRuntimeState(DataLayer.Get(), EDataLayerRuntimeState::Activated);



	// 전통적인 스타일의 레벨 로드
	/*FName DestinationLevel = CurrentStageData->StageName;
	FLatentActionInfo LatentActionInfo;
	LatentActionInfo.CallbackTarget = this;
	LatentActionInfo.UUID = AID_Loading;
	LatentActionInfo.Linkage = LID_Link;
	LatentActionInfo.ExecutionFunction = FName(TEXT("OnStreamLevelLoaded"));

	UGameplayStatics::LoadStreamLevel(this, DestinationLevel, true, false, LatentActionInfo);*/


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
			OnStageChanged.Broadcast(CurrentStageData, BeforeStageData);
			UGameplayStatics::UnloadStreamLevel(this, BeforeStageName, FLatentActionInfo(), false);
			BeforeStageData = nullptr;
			OnSuccessStageLoaded.Broadcast();
			ReadyStage();
		}), 0.2f, false);

}	