// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/DWCharacter.h"
#include "Engine/LocalPlayer.h"
#include "AbilitySystemComponent.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ADWCharacter

ADWCharacter::ADWCharacter()
{
	
}

void ADWCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

UAbilitySystemComponent* ADWCharacter::GetAbilitySystemComponent() const
{
	return ASC;
}

void ADWCharacter::Attack()
{
}

void ADWCharacter::InitializeDefaultAttributes()
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.0f);
}

void ADWCharacter::InitializeDefaultAbilities()
{
	if (ASC)
	{
		for (const auto& StartAbility : StartAbilities)
		{
			FGameplayAbilitySpec StartSpec(StartAbility);
			ASC->GiveAbility(StartSpec);
		}
	}
}

void ADWCharacter::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level)
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);

	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);

	FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void ADWCharacter::OnOutOfHealth()
{

}
