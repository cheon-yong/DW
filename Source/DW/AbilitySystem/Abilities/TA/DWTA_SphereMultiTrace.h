// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/TA/DWTA_Trace.h"
#include "DWTA_SphereMultiTrace.generated.h"

/**
 * 
 */
UCLASS()
class ADWTA_SphereMultiTrace : public ADWTA_Trace
{
	GENERATED_BODY()

protected:
	virtual FGameplayAbilityTargetDataHandle MakeTargetData() const override;
};
