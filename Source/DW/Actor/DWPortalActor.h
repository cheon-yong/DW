// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/DWEventActor.h"
#include "DWPortalActor.generated.h"

/**
 * 
 */
UCLASS()
class DW_API ADWPortalActor : public ADWEventActor
{
	GENERATED_BODY()
	
public:

	virtual void ActivateActor_Implementation() override; 
};
