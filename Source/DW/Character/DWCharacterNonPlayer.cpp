// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DWCharacterNonPlayer.h"
#include "AbilitySystem/Abilities/DWGA_MonsterAttack.h"
#include "AbilitySystem/Attributes/DWAttributeSet.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "AIController.h"
#include "BrainComponent.h"
#include <BehaviorTree/BehaviorTreeComponent.h>

ADWCharacterNonPlayer::ADWCharacterNonPlayer()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	
	AttributeSet = CreateDefaultSubobject<UDWAttributeSet>(TEXT("AttributeSet"));
}

void ADWCharacterNonPlayer::BeginPlay()
{
	Super::BeginPlay();

	ASC->InitAbilityActorInfo(this, this);
	InitializeDefaultAbilities();
	InitializeDefaultAttributes();

	if (const UDWAttributeSet* CurrentAttributeSet = ASC->GetSet<UDWAttributeSet>())
	{
		CurrentAttributeSet->OnOutOfHealth.AddUObject(this, &ThisClass::OnOutOfHealth);
	}

	FGameplayCueParameters CueParams;
	CueParams.Instigator = this;
	CueParams.RawMagnitude = CueTime;
	ASC->ExecuteGameplayCue(SpawnTag, CueParams);
}

void ADWCharacterNonPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ADWCharacterNonPlayer::NPCMeshLoadCompleted()
{
}

void ADWCharacterNonPlayer::OnOutOfHealth(AActor* Target, AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue)
{
	Super::OnOutOfHealth(Target, DamageInstigator, DamageCauser, DamageEffectSpec, DamageMagnitude, OldValue, NewValue);

	StopAI();
}

void ADWCharacterNonPlayer::StopAI()
{
	if (AAIController* AIController = UAIBlueprintHelperLibrary::GetAIController(this))
	{
		if (UBehaviorTreeComponent* BehaviorTreeComp = Cast<UBehaviorTreeComponent>(AIController->GetBrainComponent()))
		{
			BehaviorTreeComp->StopTree();
		}
	}
}


float ADWCharacterNonPlayer::GetAIPatrolRadius()
{
	return 500.0f;
}

float ADWCharacterNonPlayer::GetAIDetectRange()
{
	return 500.0f;
}

float ADWCharacterNonPlayer::GetAIAttackRange()
{
	return AttributeSet->GetAttackRange();
}

float ADWCharacterNonPlayer::GetAITurnSpeed()
{
	return 2.0f;
}

void ADWCharacterNonPlayer::SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished)
{
	OnAttackFinished = InOnAttackFinished;
}

void ADWCharacterNonPlayer::AttackByAI()
{
	if (ASC)
	{
		FGameplayAbilitySpec AbilitySpec(AttackAbility);
		ASC->TryActivateAbility(AbilitySpec.Handle);
	}
}
