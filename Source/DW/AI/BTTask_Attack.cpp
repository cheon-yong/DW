// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Attack.h"
#include "AIController.h"
#include "Interface/DWCharacterAIInterface.h"
#include <AbilitySystemComponent.h>
#include <Character/DWCharacterNonPlayer.h>
#include "Tag/DWGameplayTag.h"

UBTTask_Attack::UBTTask_Attack()
{
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}

	IDWCharacterAIInterface* AIPawn = Cast<IDWCharacterAIInterface>(ControllingPawn);
	if (nullptr == AIPawn)
	{
		return EBTNodeResult::Failed;
	}

	if (ADWCharacterNonPlayer* NPC = Cast<ADWCharacterNonPlayer>(ControllingPawn))
	{
		UAbilitySystemComponent* ASC = NPC->GetAbilitySystemComponent();
		if (ASC)
		{
			FGameplayTagContainer TagContainer;
			TagContainer.AddTag(DWTAG_EVENT_MONSTER_ATTACK);
			ASC->TryActivateAbilitiesByTag(TagContainer);
			return EBTNodeResult::Succeeded;
		}
	}
	

	//FAICharacterAttackFinished OnAttackFinished;
	//OnAttackFinished.BindLambda(
	//	[&]()
	//	{
	//		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	//	}
	//);

	//AIPawn->SetAIAttackDelegate(OnAttackFinished);
	//AIPawn->AttackByAI();
	return EBTNodeResult::InProgress;
}