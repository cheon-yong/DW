// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DWCharacterNonPlayer.h"
#include "AbilitySystem/Attributes/DWAttributeSet.h"

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
}

void ADWCharacterNonPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ADWCharacterNonPlayer::NPCMeshLoadCompleted()
{
}

float ADWCharacterNonPlayer::GetAIPatrolRadius()
{
	return 800.0f;
}

float ADWCharacterNonPlayer::GetAIDetectRange()
{
	return 400.0f;
}

float ADWCharacterNonPlayer::GetAIAttackRange()
{
	return 0.0f;
}

float ADWCharacterNonPlayer::GetAITurnSpeed()
{
	return 2.0f;
}

void ADWCharacterNonPlayer::SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished)
{
}

void ADWCharacterNonPlayer::AttackByAI()
{
	//Attack();
}
