// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_WithGameplayTag.h"
#include "AbilitySystemBlueprintLibrary.h"

UAnimNotify_WithGameplayTag::UAnimNotify_WithGameplayTag()
{
	Magnitude = 1.0f;
}

FString UAnimNotify_WithGameplayTag::GetNotifyName_Implementation() const
{
	return TEXT("TagEvent");
}

void UAnimNotify_WithGameplayTag::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		AActor* OwnerActor = MeshComp->GetOwner();
		if (OwnerActor)
		{
			FGameplayEventData PayloadData;
			PayloadData.EventMagnitude = Magnitude;
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerActor, TriggerGameplayTag, PayloadData);
		}
	}
}
