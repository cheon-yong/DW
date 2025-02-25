// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Character/DWCharacter.h"
#include "Interface/DWCharacterAIInterface.h"
#include "Engine/StreamableManager.h"

#include "DWCharacterNonPlayer.generated.h"

/**
 * 
 */
UCLASS()
class DW_API ADWCharacterNonPlayer : public ADWCharacter, public IDWCharacterAIInterface
{
	GENERATED_BODY()
	
public:
	ADWCharacterNonPlayer();

protected:
	virtual void PostInitializeComponents() override;

protected:
	//void SetDead() override;
	void NPCMeshLoadCompleted();

	UPROPERTY(config)
	TArray<FSoftObjectPath> NPCMeshes;

	TSharedPtr<FStreamableHandle> NPCMeshHandle;
	// AI Section
protected:
	virtual float GetAIPatrolRadius() override;
	virtual float GetAIDetectRange() override;
	virtual float GetAIAttackRange() override;
	virtual float GetAITurnSpeed() override;

	virtual void SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished) override;
	virtual void AttackByAI() override;

	FAICharacterAttackFinished OnAttackFinished;
	
};
