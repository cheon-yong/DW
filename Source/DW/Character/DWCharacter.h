// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "DWCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UGameplayEffect;
class UAnimMontage;
class UGameplayAbility;
class UDWAttributeSet;
struct FGameplayEffectSpec;
struct FGameplayTag;

class UQuestDefinition;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game, Blueprintable)
class ADWCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ADWCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UDWAttributeSet* GetSet() const { return AttributeSet; }

protected:
	virtual void BeginPlay();
	
	virtual void Attack();

	virtual void InitializeDefaultAttributes();

	virtual void InitializeDefaultAbilities();

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level);

	virtual void OnOutOfHealth(AActor* Target, AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue);

	void SetDead();

	void PlayDeadAnimation();

public:
	UPROPERTY(BlueprintReadOnly, Category = GAS)
	TObjectPtr<UAbilitySystemComponent> ASC;

	UPROPERTY(BlueprintReadOnly, Category = GAS)
	TObjectPtr<UDWAttributeSet> AttributeSet;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = GAS)
	TObjectPtr<UAnimMontage> DeathMontage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = GAS)
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(EditAnywhere, Category = GAS)
	TArray<TSubclassOf<UGameplayAbility>> StartAbilities;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GAS, meta = (Categories="GameplayCue"))
	FGameplayTag SpawnTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GAS)
	float CueTime = 0.f;
};

