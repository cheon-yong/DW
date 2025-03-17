// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Quest/Category/QuestCategory.h"
#include "QuestCategory_Visit.generated.h"

/**
 * 
 */
UCLASS()
class DW_API UQuestCategory_Visit : public UQuestCategory
{
	GENERATED_BODY()
	
	
public:
	virtual void Bind() override;
	
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	
	int32 SuccessCounter = 0;
};
