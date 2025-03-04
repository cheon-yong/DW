// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/MonsterSpawnComponent.h"
#include "Actor/DWMonsterSpawnPoint.h"
#include "EngineUtils.h"
#include "Game/DWGameMode.h"
#include "Tag/DWGameplayTag.h"
#include "Game/SpawnMonsterData.h"
#include "Character/DWCharacterNonPlayer.h"
#include "NavigationSystem.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "AbilitySystem/Attributes/DWAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Game/DWStageData.h"

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
		LoadSpawnMonsterData();
	}
	else if (NewStateTag == DWTAG_GAME_STATE_PLAYING)
	{
		StartSpawnMonster();
	}
	else if (NewStateTag == DWTAG_GAME_STATE_DEFEATED)
	{
		StopSpawnMonster();
		StopAllAI();
	}
	else if (NewStateTag == DWTAG_GAME_STATE_CLEAR)
	{
		StopSpawnMonster();
		StopAllAI();
	}
	else
	{

	}
}

void UMonsterSpawnComponent::SetSpawnMonsterData(USpawnMonsterData* InSpawnMonsterData)
{
	SpawnMonsterData = InSpawnMonsterData;
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

void UMonsterSpawnComponent::LoadSpawnMonsterData()
{
	if (ADWGameMode* GameMode = Cast<ADWGameMode>(GetWorld()->GetAuthGameMode()))
	{
		SpawnMonsterData = GameMode->GetCurrentStageData().MonsterData;
	}
}


void UMonsterSpawnComponent::StartSpawnMonster()
{
	for (const FSpawnData& MonsterData : SpawnMonsterData->SpawnDatas)
	{
		FTimerHandle TimerHandle;
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUFunction(this, FName("SpawnMonster"), MonsterData.Monster);
		GetWorldTimerManager().SetTimer(
			TimerHandle,
			TimerDelegate,
			MonsterData.SpawnInterval,
			true
		);

		TimerDelegates.Add(TimerHandle, TimerDelegate);
	}
}

void UMonsterSpawnComponent::StopAllAI()
{
	for (ADWCharacterNonPlayer* Monster : Monsters)
	{
		Monster->StopAI();
	}
}


void UMonsterSpawnComponent::OnMonsterDead(AActor* Target, AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue)
{
	if (ADWCharacterNonPlayer* Monster = Cast<ADWCharacterNonPlayer>(Target))
	{
		FTimerHandle TimerHandle;
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUFunction(this, FName("DestroyMonster"), Monster);
		GetWorldTimerManager().SetTimer(
			TimerHandle, 
			TimerDelegate,
			1.0f,
			false,
			1.2f
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

void UMonsterSpawnComponent::DestroyMonster(ADWCharacterNonPlayer* Monster)
{
	if (Monster != nullptr)
	{
		Monsters.Remove(Monster);
		Monster->Destroy();
		OnMonsterChanged.Broadcast(Monsters.Num());
		if (ADWGameMode* GameMode = Cast<ADWGameMode>(GetWorld()->GetAuthGameMode()))
		{
			int32 CurrentScore = GameMode->GetScore();
			GameMode->SetScore(CurrentScore + 1);
		}
	}
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
	NewActor->GetSet()->OnOutOfHealth.AddUObject(this, &ThisClass::OnMonsterDead);
	NewActor->FinishSpawning(FTransform::Identity, /*bIsDefaultTransform=*/ true);
	
	Monsters.Add(NewActor);
	OnMonsterChanged.Broadcast(Monsters.Num());
}
	