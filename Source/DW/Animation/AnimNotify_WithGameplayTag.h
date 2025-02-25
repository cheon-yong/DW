// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GameplayTagContainer.h"

#include "AnimNotify_WithGameplayTag.generated.h"

/**
 * 
 */
UCLASS()
class DW_API UAnimNotify_WithGameplayTag : public UAnimNotify
{
	GENERATED_BODY()

public:
	UAnimNotify_WithGameplayTag();

protected:
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY(EditAnywhere, Meta = (Categories = Event))
	FGameplayTag TriggerGameplayTag;

	UPROPERTY(EditAnywhere)
	float Magnitude;
};
