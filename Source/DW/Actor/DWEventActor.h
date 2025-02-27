// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DWEventActor.generated.h"

class USceneComponent;
class UBoxComponent;

UCLASS()
class DW_API ADWEventActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADWEventActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Event)
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Event)
	TObjectPtr<UBoxComponent> BoxComponent;
};
