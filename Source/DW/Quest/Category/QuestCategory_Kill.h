// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayEffect.h"
#include "Quest/Category/QuestCategory.h"

#include "QuestCategory_Kill.generated.h"

class AActor;
struct FGameplayEffectSpec;

/**
 * 
 */
UCLASS()
class DW_API UQuestCategory_Kill : public UQuestCategory
{
	GENERATED_BODY()
	
public:
	virtual void Bind() override;

	void OnOutOfHealth(AActor* Target, AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue);
};
