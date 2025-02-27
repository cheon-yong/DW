// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/DWMonsterSpawnPoint.h"
#include "Components/SphereComponent.h"

// Sets default values
ADWMonsterSpawnPoint::ADWMonsterSpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Area"));
	SphereComponent->SetupAttachment(RootComponent);
}
