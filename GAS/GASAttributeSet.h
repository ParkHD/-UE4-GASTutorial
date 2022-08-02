// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GASAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName)	\
		GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName) 

/**
 * 
 */
UCLASS()
class GAS_API UGASAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UGASAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// 체력
	// ReplicatedUsing지정자는 네트워크를 통해 프로퍼티를 업데이트할 때 실행되는 콜백 함수를 지정합니다.
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Health)
		FGameplayAttributeData Health;
	// 매크로를 사용하여 일부 Get및 Set, Init 등을 추가하는 상태 속성을  정의
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, Health);
	// 네트워크를 통해 새로운 Health 값이 도착할 때 호출됩니다. 
	UFUNCTION()
		virtual void OnRep_Health(const  FGameplayAttributeData& OldHealth);

	// 스태미너
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Stamina)
		FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, Stamina);
	UFUNCTION()
		virtual void OnRep_Stamina(const  FGameplayAttributeData& OldStamina);

	// 공격력
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_AttackPower)
		FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, AttackPower);
	UFUNCTION()
		virtual void OnRep_AttackPower(const  FGameplayAttributeData& OldAttackPower);
};
