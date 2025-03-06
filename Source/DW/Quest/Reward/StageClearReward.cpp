// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/Reward/StageClearReward.h"
#include "Game/StageComponent.h"
#include "Game/DWGameState.h"

void UStageClearReward::Give()
{
	if (ADWGameState* DWGameState = Cast<ADWGameState>(GetWorld()->GetGameState()))
	{
		if (UStageComponent* StageComp = DWGameState->GetComponentByClass<UStageComponent>())
		{
			StageComp->CompleteStage();
		}
	}
}
