// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DWPlayerState.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/Attributes/DWAttributeSet.h"

ADWPlayerState::ADWPlayerState()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	AttributeSet = CreateDefaultSubobject<UDWAttributeSet>(TEXT("AttributeSet"));
}

UAbilitySystemComponent* ADWPlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}
