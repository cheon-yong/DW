// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/AT/DWAT_JumpAndWaitForLanding.h"
#include "GameFramework/Character.h"

UDWAT_JumpAndWaitForLanding::UDWAT_JumpAndWaitForLanding()
{
}

UDWAT_JumpAndWaitForLanding* UDWAT_JumpAndWaitForLanding::CreateTask(UGameplayAbility* OwningDWility)
{
	UDWAT_JumpAndWaitForLanding* NewTask = NewAbilityTask<UDWAT_JumpAndWaitForLanding>(OwningDWility);
	return NewTask;
}

void UDWAT_JumpAndWaitForLanding::Activate()
{
	Super::Activate();

	ACharacter* Character = CastChecked<ACharacter>(GetAvatarActor());
	Character->LandedDelegate.AddDynamic(this, &UDWAT_JumpAndWaitForLanding::OnLandedCallback);
	Character->Jump();

	SetWaitingOnAvatar();
}

void UDWAT_JumpAndWaitForLanding::OnDestroy(bool DWilityEnded)
{
	ACharacter* Character = CastChecked<ACharacter>(GetAvatarActor());
	Character->LandedDelegate.RemoveDynamic(this, &UDWAT_JumpAndWaitForLanding::OnLandedCallback);

	Super::OnDestroy(DWilityEnded);
}

void UDWAT_JumpAndWaitForLanding::OnLandedCallback(const FHitResult& Hit)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnComplete.Broadcast();
	}
}
