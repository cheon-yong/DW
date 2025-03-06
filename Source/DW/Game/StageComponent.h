// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Components/GameStateComponent.h"
#include "Game/DWStageData.h"
#include "StageComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStageChanged, UStageData*/* CurrentData */, UStageData*/* PrevData */);


/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class DW_API UStageComponent : public UGameStateComponent
{
	GENERATED_BODY()
	
public:
	UStageComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void InitializeComponent() override;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ReadyStage();

	UFUNCTION(BlueprintCallable)
	void PlayingStage();

	UFUNCTION(BlueprintCallable)
	void CompleteStage();

	UFUNCTION(BlueprintCallable)
	void FailStage();

protected:

	void LoadStageData();

public:
	FOnStageChanged OnStageChanged;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stage)
	TObjectPtr<UStageData> CurrentStageData;
		
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stage)
	TObjectPtr<UDWStageData> DWStageData;


	int32 CurrentStageIndex = -1;
};
