// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/AT/DWAT_Trace.h"
#include "AbilitySystem/Abilities/TA/DWTA_Trace.h"
#include "AbilitySystemComponent.h"

UDWAT_Trace::UDWAT_Trace()
{
}

UDWAT_Trace* UDWAT_Trace::CreateTask(UGameplayAbility* OwningDWility, TSubclassOf<ADWTA_Trace> TargetActorClass)
{
	UDWAT_Trace* NewTask = NewAbilityTask<UDWAT_Trace>(OwningDWility);
	NewTask->TargetActorClass = TargetActorClass;
	return NewTask;
}

void UDWAT_Trace::Activate()
{
	Super::Activate();

	SpawnAndInitializeTargetActor();
	FinalizeTargetActor();

	SetWaitingOnAvatar();
}

void UDWAT_Trace::OnDestroy(bool DWilityEnded)
{
	if (SpawnedTargetActor)
	{
		SpawnedTargetActor->Destroy();
	}

	Super::OnDestroy(DWilityEnded);
}

void UDWAT_Trace::SpawnAndInitializeTargetActor()
{
	SpawnedTargetActor = Cast<ADWTA_Trace>(Ability->GetWorld()->SpawnActorDeferred<AGameplayAbilityTargetActor>(TargetActorClass, FTransform::Identity, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn));
	if (SpawnedTargetActor)
	{
		SpawnedTargetActor->SetShowDebug(true);
		SpawnedTargetActor->TargetDataReadyDelegate.AddUObject(this, &UDWAT_Trace::OnTargetDataReadyCallback);
	}
}

void UDWAT_Trace::FinalizeTargetActor()
{
	UAbilitySystemComponent* ASC = AbilitySystemComponent.Get();
	if (ASC)
	{
		const FTransform SpawnTransform = ASC->GetAvatarActor()->GetTransform();
		SpawnedTargetActor->FinishSpawning(SpawnTransform);

		ASC->SpawnedTargetActors.Push(SpawnedTargetActor);
		SpawnedTargetActor->StartTargeting(Ability);
		SpawnedTargetActor->ConfirmTargeting();
	}
}

void UDWAT_Trace::OnTargetDataReadyCallback(const FGameplayAbilityTargetDataHandle& DataHandle)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnComplete.Broadcast(DataHandle);
	}

	EndTask();
}
