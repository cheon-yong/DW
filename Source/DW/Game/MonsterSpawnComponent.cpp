// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/MonsterSpawnComponent.h"
#include "Actor/DWMonsterSpawnPoint.h"
#include "EngineUtils.h"
#include "Game/DWGameMode.h"
#include "Tag/DWGameplayTag.h"
#include "Game/SpawnMonsterData.h"
#include "Character/DWCharacterNonPlayer.h"
#include <NavigationSystem.h>
#include "Components/SphereComponent.h"
#include <Kismet/KismetMathLibrary.h>

UMonsterSpawnComponent::UMonsterSpawnComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UMonsterSpawnComponent::BeginPlay()
{
	Super::BeginPlay();

	if (ADWGameMode* GameMode = Cast<ADWGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->OnGameStateChanged.AddDynamic(this, &ThisClass::OnGameStateChange);
	}

	FindAllSpawnPoints();
}

void UMonsterSpawnComponent::OnGameStateChange(FGameplayTag NewStateTag)
{
	if (NewStateTag == DWTAG_GAME_STATE_READY)
	{

	}
	else if (NewStateTag == DWTAG_GAME_STATE_PLAYING)
	{
		StartSpawnMonster();
	}
	else if (NewStateTag == DWTAG_GAME_STATE_DEFEATED)
	{
		StopSpawnMonster();
	}
	else if (NewStateTag == DWTAG_GAME_STATE_CLEAR)
	{
		StopSpawnMonster();
	}
	else
	{

	}
}

void UMonsterSpawnComponent::FindAllSpawnPoints()
{
	if (UWorld* World = GetWorld())
	{
		for (TActorIterator<AActor> It(World); It; ++It)
		{
			AActor* Actor = *It;
			if (ADWMonsterSpawnPoint* SpawnPoint = Cast<ADWMonsterSpawnPoint>(Actor))
			{
				SpawnPoints.Emplace(SpawnPoint);
			}
		}
	}
}


void UMonsterSpawnComponent::StartSpawnMonster()
{
	for (const FSpawnData& MonsterData : SpawnMonsterData->SpawnDatas)
	{
		FTimerHandle TimerHandle;
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUFunction(this, FName("SpawnMonster"), MonsterData.Monster);

		TimerDelegates.Add(TimerHandle, TimerDelegate);
		GetWorldTimerManager().SetTimer(
			TimerHandle,
			TimerDelegate,
			MonsterData.SpawnInterval,
			true
		);
	}
}

void UMonsterSpawnComponent::StopSpawnMonster()
{
	TArray<FTimerHandle> Keys;
	TimerDelegates.GetKeys(Keys);
	for (FTimerHandle& Handle : Keys)
	{
		GetWorldTimerManager().ClearTimer(Handle);
	}

	TimerDelegates.Empty();
}

void UMonsterSpawnComponent::SpawnMonster(TSubclassOf<ADWCharacterNonPlayer> MonsterToSpawn)
{
	int32 RandomIndex = FMath::RandRange(0, SpawnPoints.Num() - 1);
	ADWMonsterSpawnPoint* SpawnPoint = SpawnPoints[RandomIndex];

	FNavLocation NavLocation;
	FVector Location = SpawnPoint->GetActorLocation();
	float Radius = SpawnPoint->SphereComponent->GetScaledSphereRadius();

	UNavigationSystemV1::GetNavigationSystem(GetWorld())->GetRandomReachablePointInRadius(Location, Radius, NavLocation);
	FTransform SpawnTransform = UKismetMathLibrary::MakeTransform(NavLocation, UKismetMathLibrary::FindLookAtRotation(NavLocation, Location));


	ADWCharacterNonPlayer* NewActor = GetWorld()->SpawnActorDeferred<ADWCharacterNonPlayer>(MonsterToSpawn, SpawnTransform);
	NewActor->FinishSpawning(FTransform::Identity, /*bIsDefaultTransform=*/ true);

	Monsters.Add(NewActor);
	OnMonsterChanged.Broadcast(Monsters.Num());
}
