// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DWMonsterSpawnPoint.generated.h"

class USphereComponent;

UCLASS()
class DW_API ADWMonsterSpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADWMonsterSpawnPoint();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Area)
	TObjectPtr<USphereComponent> SphereComponent;

};
