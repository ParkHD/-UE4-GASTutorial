// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GEExecMelee.generated.h"

/**
 * 
 */
UCLASS()
class GAS_API UGEExecMelee : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UGEExecMelee();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
