// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DWStageSubsystem.generated.h"

class UStageData;
class UDWStageData;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStageChanged, UStageData*/* CurrentData */, UStageData*/* PrevData */);

/**
 * 
 */
UCLASS(config = Game)
class DW_API UDWStageSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UDWStageSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable)
	void ReadyStage();

	UFUNCTION(BlueprintCallable)
	void PlayingStage();

	UFUNCTION(BlueprintCallable)
	void CompleteStage();

	UFUNCTION(BlueprintCallable)
	void FailStage();

protected:

	void LoadDefaultStageData();

	void LoadStageData();

public:
	FOnStageChanged OnStageChanged;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stage)
	TObjectPtr<UStageData> CurrentStageData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stage)
	TObjectPtr<UDWStageData> DWStageData;

	UPROPERTY(config, EditAnywhere)
	TSoftClassPtr<UDWStageData> DefaultStageDataClass;
	 

	int32 CurrentStageIndex = -1;
};
