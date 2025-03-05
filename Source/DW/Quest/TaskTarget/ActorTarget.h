// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Quest/QuestTaskTarget.h"
#include "ActorTarget.generated.h"

/**
 * 
 */
UCLASS()
class DW_API UActorTarget : public UQuestTaskTarget
{
	GENERATED_BODY()
	
public:
	virtual bool IsEqual(UObject* Object) override;
};
