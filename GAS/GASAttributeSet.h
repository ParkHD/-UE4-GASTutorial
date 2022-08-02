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

	// ü��
	// ReplicatedUsing�����ڴ� ��Ʈ��ũ�� ���� ������Ƽ�� ������Ʈ�� �� ����Ǵ� �ݹ� �Լ��� �����մϴ�.
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Health)
		FGameplayAttributeData Health;
	// ��ũ�θ� ����Ͽ� �Ϻ� Get�� Set, Init ���� �߰��ϴ� ���� �Ӽ���  ����
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, Health);
	// ��Ʈ��ũ�� ���� ���ο� Health ���� ������ �� ȣ��˴ϴ�. 
	UFUNCTION()
		virtual void OnRep_Health(const  FGameplayAttributeData& OldHealth);

	// ���¹̳�
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Stamina)
		FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, Stamina);
	UFUNCTION()
		virtual void OnRep_Stamina(const  FGameplayAttributeData& OldStamina);

	// ���ݷ�
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_AttackPower)
		FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, AttackPower);
	UFUNCTION()
		virtual void OnRep_AttackPower(const  FGameplayAttributeData& OldAttackPower);
};
