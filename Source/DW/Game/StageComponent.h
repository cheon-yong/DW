// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Components/GameStateComponent.h"
#include "Game/DWStageData.h"
#include "StageComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnStageChanged, FStageData&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnStageStateChanged, EStageState&);

UENUM(BlueprintType)
enum class EStageState : uint8
{
	None,
	Ready,
	Playing,
	Complete,
	Fail,
};

/**
 * 
 */
UCLASS(BlueprintType)
class DW_API UStageComponent : public UGameStateComponent
{
	GENERATED_BODY()
	
public:
	UStageComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void InitializeComponent() override;

	virtual void BeginPlay() override;

	void LoadStageData();

	UFUNCTION(BlueprintCallable)
	void SetStageState(EStageState NewState);
public:

	FOnStageChanged OnStageChanged;

	FOnStageStateChanged OnStageStateChanged;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stage)
	FStageData CurrentStageData;
		
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stage)
	TObjectPtr<UDWStageData> DWStageData;

	EStageState StageState = EStageState::None;

	int32 CurrentStageIndex = 0;
};
