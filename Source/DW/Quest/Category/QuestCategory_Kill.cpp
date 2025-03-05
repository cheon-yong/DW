// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/Category/QuestCategory_Kill.h"

#include "Character/DWCharacter.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/Attributes/DWAttributeSet.h"

void UQuestCategory_Kill::Bind()
{
	if (ADWCharacter* DWCharacter = Cast<ADWCharacter>(Owner))
	{
		const UDWAttributeSet* DWAttributeSet = DWCharacter->GetAbilitySystemComponent()->GetSet<UDWAttributeSet>();
		DWAttributeSet->OnOutOfHealth.AddUObject(this, &ThisClass::OnOutOfHealth);
	}
}

void UQuestCategory_Kill::OnOutOfHealth(AActor* Target, AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue)
{
	OnTaskSuccessed.Broadcast();
}
