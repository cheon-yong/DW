// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "DWAttributeSet.generated.h"


class UObject;
class UWorld;
struct FGameplayEffectSpec;

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


//DECLARE_MULTICAST_DELEGATE_SixParams(FDWAttributeEvent, AActor* /*EffectInstigator*/, AActor* /*EffectCauser*/, const FGameplayEffectSpec* /*EffectSpec*/, float /*EffectMagnitude*/, float /*OldValue*/, float /*NewValue*/);
DECLARE_MULTICAST_DELEGATE_SevenParams(FDWAttributeEvent, AActor* /*Target*/, AActor* /*EffectInstigator*/, AActor* /*EffectCauser*/, const FGameplayEffectSpec* /*EffectSpec*/, float /*EffectMagnitude*/, float /*OldValue*/, float /*NewValue*/);
/**
 * 
 */
UCLASS()
class DW_API UDWAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UDWAttributeSet();

public:

	ATTRIBUTE_ACCESSORS(UDWAttributeSet, AttackRange);
	ATTRIBUTE_ACCESSORS(UDWAttributeSet, MaxAttackRange);
	ATTRIBUTE_ACCESSORS(UDWAttributeSet, AttackRadius);
	ATTRIBUTE_ACCESSORS(UDWAttributeSet, MaxAttackRadius);
	ATTRIBUTE_ACCESSORS(UDWAttributeSet, AttackRate);
	ATTRIBUTE_ACCESSORS(UDWAttributeSet, MaxAttackRate);
	ATTRIBUTE_ACCESSORS(UDWAttributeSet, AttackSpeed);
	ATTRIBUTE_ACCESSORS(UDWAttributeSet, MaxAttackSpeed);
	ATTRIBUTE_ACCESSORS(UDWAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UDWAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UDWAttributeSet, Damage);

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	//virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
	mutable FDWAttributeEvent OnHealthChanged;
	mutable FDWAttributeEvent OnMaxHealthChanged;
	mutable FDWAttributeEvent OnOutOfHealth;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackRange;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAttackRange;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackRadius;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAttackRadius;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackRate;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAttackRate;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAttackSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Damage;

	bool bOutOfHealth = false;

	//friend class UABGE_AttackDamage;

private:
	float MaxHealthBeforeAttributeChange;
	float HealthBeforeAttributeChange;
};
