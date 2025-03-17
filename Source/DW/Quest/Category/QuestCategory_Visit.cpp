// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/Category/QuestCategory_Visit.h"

#include "Components/ShapeComponent.h"

void UQuestCategory_Visit::Bind()
{
	if (UShapeComponent* ShapeComponent = Owner->GetComponentByClass<UShapeComponent>())
	{
		ShapeComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnComponentBeginOverlap);
	}
}

void UQuestCategory_Visit::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (SuccessCounter != 0)
		return;

	SuccessCounter++;
	OnTaskSuccessed.Broadcast();
}
