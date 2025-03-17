// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/DWEventActor.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
ADWEventActor::ADWEventActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = SceneComponent;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ADWEventActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADWEventActor::ActivateActor_Implementation()
{
}

