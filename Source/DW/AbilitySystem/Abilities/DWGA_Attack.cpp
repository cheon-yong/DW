// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/DWGA_Attack.h"
#include "Character/DWCharacterPlayer.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/DWComboActionData.h"
#include "Tag/DWGameplayTag.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

UDWGA_Attack::UDWGA_Attack()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UDWGA_Attack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ADWCharacterPlayer* DWCharacter = CastChecked<ADWCharacterPlayer>(ActorInfo->AvatarActor.Get());
	CurrentComboData = DWCharacter->GetComboActionData();
	DWCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);	

	// PlayAbilityTask
	AttackMontage = DWCharacter->GetComboActionMontage();
	FName NextSection = GetNextSection();
	UAbilityTask_PlayMontageAndWait* PlayAttackTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("PlayAttack"), AttackMontage, 1.0f, NextSection);
	PlayAttackTask->OnCompleted.AddDynamic(this, &UDWGA_Attack::OnCompleteCallback);
	PlayAttackTask->OnInterrupted.AddDynamic(this, &UDWGA_Attack::OnInterruptedCallback);
	PlayAttackTask->ReadyForActivation();

	// Attack Effect
	int32 SectionIndex = AttackMontage->GetSectionIndex(NextSection);
	float LifeTime = AttackMontage->GetSectionLength(SectionIndex);


	ExecuteGameplayCue(LifeTime, ActorInfo->AvatarActor.Get());
	StartComboTimer();
}

void UDWGA_Attack::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	if (!ComboTimerHandle.IsValid())
	{
		HasNextComboInput = false;
	}
	else
	{
		HasNextComboInput = true;
	}
}

void UDWGA_Attack::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UDWGA_Attack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	ADWCharacterPlayer* DWCharacter = CastChecked<ADWCharacterPlayer>(ActorInfo->AvatarActor.Get());
	DWCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

	CurrentComboData = nullptr;
	CurrentCombo = 0;
	HasNextComboInput = false;
}

void UDWGA_Attack::ExecuteGameplayCue(float LifeTime, AActor* Instigator)
{
	FGameplayCueParameters CueParam;
	CueParam.RawMagnitude = LifeTime;
	CueParam.Instigator = Instigator;

	CurrentActorInfo->AbilitySystemComponent->ExecuteGameplayCue(GameplayCueTag, CueParam);
}

void UDWGA_Attack::OnCompleteCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UDWGA_Attack::OnInterruptedCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

FName UDWGA_Attack::GetNextSection()
{
	CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, CurrentComboData->MaxComboCount);
	FName NextSection = *FString::Printf(TEXT("%s%d"), *CurrentComboData->MontageSectionNamePrefix, CurrentCombo);
	return NextSection;
}

void UDWGA_Attack::StartComboTimer()
{
	int32 ComboIndex = CurrentCombo - 1;
	ensure(CurrentComboData->EffectiveFrameCount.IsValidIndex(ComboIndex));

	const float ComboEffectiveTime = CurrentComboData->EffectiveFrameCount[ComboIndex] / CurrentComboData->FrameRate;
	if (ComboEffectiveTime > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &UDWGA_Attack::CheckComboInput, ComboEffectiveTime, false);
	}
}

void UDWGA_Attack::CheckComboInput()
{
	ComboTimerHandle.Invalidate();
	if (HasNextComboInput)
	{
		FName NextSection = GetNextSection();
		MontageJumpToSection(NextSection);

		int32 SectionIndex = AttackMontage->GetSectionIndex(NextSection);
		float LifeTime = AttackMontage->GetSectionLength(SectionIndex);

		ExecuteGameplayCue(LifeTime, CurrentActorInfo->AvatarActor.Get());

		StartComboTimer();
		HasNextComboInput = false;
	}
}
