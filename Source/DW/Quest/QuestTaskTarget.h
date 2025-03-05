// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "QuestTaskTarget.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Const, Abstract)
class DW_API UQuestTaskTarget : public UObject
{
	GENERATED_BODY()
	
public:
	virtual bool IsEqual(UObject* Object) PURE_VIRTUAL(UQuestTaskAction::IsEqual, return false;);
};
