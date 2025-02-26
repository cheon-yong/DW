// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/DWGA_MonsterAttack.h"

#include "Character/DWCharacter.h"
#include "AbilitySystem/Attributes/DWAttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"

UDWGA_MonsterAttack::UDWGA_MonsterAttack()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UDWGA_MonsterAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ADWCharacter* DWCharacter = CastChecked<ADWCharacter>(ActorInfo->AvatarActor.Get());
	DWCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	const UDWAttributeSet* AttributeSet = DWCharacter->AttributeSet;

	float AttackSpeed = AttributeSet->GetAttackSpeed() / 100;
	UAbilityTask_PlayMontageAndWait* PlayAttackTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("PlayAttack"), AttackMontage, AttackSpeed);
	PlayAttackTask->OnCompleted.AddDynamic(this, &UDWGA_MonsterAttack::OnCompleteCallback);
	PlayAttackTask->OnInterrupted.AddDynamic(this, &UDWGA_MonsterAttack::OnInterruptedCallback);
	PlayAttackTask->ReadyForActivation();
}

void UDWGA_MonsterAttack::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UDWGA_MonsterAttack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	ADWCharacter* DWCharacter = CastChecked<ADWCharacter>(ActorInfo->AvatarActor.Get());
	DWCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void UDWGA_MonsterAttack::OnCompleteCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UDWGA_MonsterAttack::OnInterruptedCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
