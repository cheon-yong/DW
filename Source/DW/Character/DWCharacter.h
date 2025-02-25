// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "AbilitySystemInterface.h"
#include "DWCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

class UAnimMontage;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ADWCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ADWCharacter();

protected:

	// To add mapping context
	virtual void BeginPlay();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	virtual void Attack();

	UFUNCTION()
	virtual void OnOutOfHealth();

public:

	UPROPERTY(BlueprintReadOnly, Category = GAS)
	TObjectPtr<UAbilitySystemComponent> ASC;
};

