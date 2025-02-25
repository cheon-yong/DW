// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/DWCharacter.h"
#include "Engine/LocalPlayer.h"

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

void ADWCharacter::OnOutOfHealth()
{

}
