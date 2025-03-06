// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/DWStageData.h"
#include "Quest/QuestDefinition.h"

void UStageData::Ready()
{
	StageState = EStageState::Ready;
	OnReady.Broadcast(this);
}

void UStageData::Playing()
{
	StageState = EStageState::Playing;
	OnPlaying.Broadcast(this);
}

void UStageData::Fail()
{
	StageState = EStageState::Fail;
	OnFail.Broadcast(this);
}

void UStageData::Complete()
{
	StageState = EStageState::Complete;
	OnComplete.Broadcast(this);
}

void UStageData::Clear()
{
	OnReady.Clear();
	OnPlaying.Clear();
	OnFail.Clear();
	OnComplete.Clear();
}
