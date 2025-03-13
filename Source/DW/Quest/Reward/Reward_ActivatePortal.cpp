// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/Reward/Reward_ActivatePortal.h"

#include "Actor/DWPortalActor.h"

#include "EngineUtils.h"

void UReward_ActivatePortal::Give()
{
	// Find Portal and Activate that
	if (UWorld* World = GetWorld())
	{
		for (TActorIterator<AActor> It(World); It; ++It)
		{
			AActor* Actor = *It;
			if (ADWPortalActor* Portal = Cast<ADWPortalActor>(Actor))
			{
				Portal->ActivateActor();
			}
		}
	}
}
