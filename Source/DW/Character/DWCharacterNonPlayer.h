// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Character/DWCharacter.h"
#include "Interface/DWCharacterAIInterface.h"
#include "Engine/StreamableManager.h"

#include "DWCharacterNonPlayer.generated.h"

class UGameplayAbility;
/**
 * 
 */
UCLASS()
class DW_API ADWCharacterNonPlayer : public ADWCharacter, public IDWCharacterAIInterface
{
	GENERATED_BODY()
	
public:
	ADWCharacterNonPlayer();

	void StopAI();

protected:
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

protected:
	virtual float GetAIPatrolRadius() override;
	virtual float GetAIDetectRange() override;
	virtual float GetAIAttackRange() override;
	virtual float GetAITurnSpeed() override;

	virtual void SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished) override;
	virtual void AttackByAI() override;

	FAICharacterAttackFinished OnAttackFinished;

	//void SetDead() override;
	void NPCMeshLoadCompleted();

	virtual void OnOutOfHealth(AActor* Target, AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue) override;

protected:
	UPROPERTY(config)
	TArray<FSoftObjectPath> NPCMeshes;

	TSharedPtr<FStreamableHandle> NPCMeshHandle;
	// AI Section
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GAS)
	TSubclassOf<UGameplayAbility> AttackAbility;
};
