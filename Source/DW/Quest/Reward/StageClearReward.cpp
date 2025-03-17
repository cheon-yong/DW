// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/Reward/StageClearReward.h"
#include "Game/DWStageSubsystem.h"
#include "Game/DWGameState.h"

void UStageClearReward::Give()
{
	if (UGameInstance* GameInstance = GetWorld()->GetGameInstance())
	{
		if (UDWStageSubsystem* StageSubsystem = GameInstance->GetSubsystem<UDWStageSubsystem>())
		{
			StageSubsystem->CompleteStage();
		}
	}
}
