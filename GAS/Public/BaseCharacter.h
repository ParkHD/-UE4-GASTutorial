// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"
#include "BaseCharacter.generated.h"

// 전방선언 하면 컴파일 시간이 단축
class UBaseAttributeSet;

UCLASS()
class GAS_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BaseCharacter")
		UAbilitySystemComponent* AbilitySystemComponent;

	// Ability초기화
	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
		void InitializeAbility(TSubclassOf<UGameplayAbility> AbilityToGet, int32 AbilityLevel);
	//Initialize Abilities Multi
	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
		void InitializeAbilityMulti(TArray<TSubclassOf<UGameplayAbility>> AbilitiesToAcquire, int32 AbilityLevel);

	//Remove Abilities with Tag
	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
		void RemoveAbilityWithTags(FGameplayTagContainer TagContainer);

	//Change Ability Level with Tag
	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
		void ChangeAbilityLevelWithTags(FGameplayTagContainer TagContainer, int32 NewLevel);

	//Cancel Ability With Tag
	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
		void CancelAbilityWithTags(FGameplayTagContainer WithTags, FGameplayTagContainer WithoutTags);

	//Add Loose Gameplay Tag
	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
		void AddLooseGameplayTag(FGameplayTag TagToAdd);

	//Remove Loose Gameplay Tag
	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
		void RemoveLooseGameplayTags(FGameplayTag TagsToRemove);

	//Apply GE to Target Data
	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
		void ApplyGEToTargetData(const FGameplayEffectSpecHandle& GESpec, const FGameplayAbilityTargetDataHandle& TargetData);

	//Modify Health Attributes
	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
		void SetHealthValues(float NewHealth, float NewMaxHealth);

	//Modify Mana Attributes
	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
		void SetManaValues(float NewMana, float NewMaxMana);

	//Modify Stamina Attributes
	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
		void SetStaminaValues(float NewStamina, float NewMaxStamina);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;

	// Attribute Set Component
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BaseCharacter")
		const class UBaseAttributeSet* BaseAttributeSetComp;

	// 속성값 가져오는 함수
	UFUNCTION(BlueprintPure, Category = "BaseCharacter")
		void GetHealthValues(float& Health, float& MaxHealth);
	UFUNCTION(BlueprintPure, Category = "BaseCharacter")
		void GetManaValues(float& Mana, float& MaxMana);
	UFUNCTION(BlueprintPure, Category = "BaseCharacter")
		void GetStaminaValues(float& Stamina, float& MaxStamina);

	void OnHealthChagedNative(const FOnAttributeChangeData& Data);
	void OnManaChagedNative(const FOnAttributeChangeData& Data);
	void OnStaminaChagedNative(const FOnAttributeChangeData& Data);

	// 블루프린트에서 정의할 함수
	UFUNCTION(BlueprintImplementableEvent, Category = "BaseCharacter")
		void OnHealthChanged(float OldValue, float NewValue);
	UFUNCTION(BlueprintImplementableEvent, Category = "BaseCharacter")
		void OnManaChanged(float OldValue, float NewValue);
	UFUNCTION(BlueprintImplementableEvent, Category = "BaseCharacter")
		void OnStaminaChanged(float OldValue, float NewValue);
};
