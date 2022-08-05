// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "BaseAttributeSet.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (AbilitySystemComponent)
	{
		// AbilitySystemComponent의 데이터테이블에 접근하여 AttributeSet값을 초기화 시킨다.
		BaseAttributeSetComp = AbilitySystemComponent->GetSet<UBaseAttributeSet>();

		// 속성값이 변했을 때 호출되는 함수를 바인딩 해준다.
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSetComp->GetHealthAttribute()).AddUObject(this, &ABaseCharacter::OnHealthChagedNative);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSetComp->GetManaAttribute()).AddUObject(this, &ABaseCharacter::OnManaChagedNative);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSetComp->GetStaminaAttribute()).AddUObject(this, &ABaseCharacter::OnStaminaChagedNative);
		//const_cast<UBaseAttributeSet*>(BaseAttributeSetComp)->SpeedChangeDelegate.AddDynamic(this, &ABaseCharacter::OnSpeedChangeNative);
	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseCharacter::InitializeAbility(TSubclassOf<UGameplayAbility> AbilityToGet, int32 AbilityLevel)
{
	if(AbilitySystemComponent)
	{
		if(HasAuthority() && AbilityToGet)
		{
			// Ability를 수여한다.
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(AbilityToGet, AbilityLevel, 0));
		}
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
void ABaseCharacter::GetHealthValues(float& Health, float& MaxHealth)
{
	if (BaseAttributeSetComp)
	{
		Health = BaseAttributeSetComp->GetHealth();
		MaxHealth = BaseAttributeSetComp->GetMaxHealth();
	}
}

void ABaseCharacter::GetManaValues(float& Mana, float& MaxMana)
{
	if (BaseAttributeSetComp)
	{
		Mana = BaseAttributeSetComp->GetMana();
		MaxMana = BaseAttributeSetComp->GetMaxMana();
	}
}

void ABaseCharacter::GetStaminaValues(float& Stamina, float& MaxStamina)
{
	if (BaseAttributeSetComp)
	{
		Stamina = BaseAttributeSetComp->GetStamina();
		MaxStamina = BaseAttributeSetComp->GetMaxStamina();
	}
}
void ABaseCharacter::GetShieldValues(float& Shield, float& MaxShield)
{
	Shield = BaseAttributeSetComp->GetShield();
	MaxShield = BaseAttributeSetComp->GetMaxShield();
}
void ABaseCharacter::OnHealthChagedNative(const FOnAttributeChangeData& Data)
{
	OnHealthChanged(Data.OldValue, Data.NewValue);
}

void ABaseCharacter::OnManaChagedNative(const FOnAttributeChangeData& Data)
{
	OnManaChanged(Data.OldValue, Data.NewValue);
}

void ABaseCharacter::OnStaminaChagedNative(const FOnAttributeChangeData& Data)
{
	OnStaminaChanged(Data.OldValue, Data.NewValue);
}

void ABaseCharacter::InitializeAbilityMulti(TArray<TSubclassOf<UGameplayAbility>> AbilitiesToAcquire, int32 AbilityLevel)
{
	for (TSubclassOf<UGameplayAbility> AbilitItem : AbilitiesToAcquire)
	{
		InitializeAbility(AbilitItem, AbilityLevel);
	}
}
void ABaseCharacter::RemoveAbilityWithTags(FGameplayTagContainer TagContainer)
{
	TArray<FGameplayAbilitySpec*> MatchingAbilities;
	AbilitySystemComponent->GetActivatableGameplayAbilitySpecsByAllMatchingTags(TagContainer, MatchingAbilities, true);
	for (FGameplayAbilitySpec* Spec : MatchingAbilities)
	{
		AbilitySystemComponent->ClearAbility(Spec->Handle);
	}
}

void ABaseCharacter::ChangeAbilityLevelWithTags(FGameplayTagContainer TagContainer, int32 NewLevel)
{
	TArray<FGameplayAbilitySpec*> MatchingAbility;
	AbilitySystemComponent->GetActivatableGameplayAbilitySpecsByAllMatchingTags(TagContainer, MatchingAbility, true);
	for (FGameplayAbilitySpec* Spec : MatchingAbility)
	{
		Spec->Level = NewLevel;
	}
}

void ABaseCharacter::CancelAbilityWithTags(FGameplayTagContainer WithTags, FGameplayTagContainer WithoutTags)
{
	AbilitySystemComponent->CancelAbilities(&WithTags, &WithoutTags, nullptr);
}

void ABaseCharacter::AddLooseGameplayTag(FGameplayTag TagToAdd)
{
	GetAbilitySystemComponent()->AddLooseGameplayTag(TagToAdd);
	GetAbilitySystemComponent()->SetTagMapCount(TagToAdd, 1);
}

void ABaseCharacter::RemoveLooseGameplayTags(FGameplayTag TagsToRemove)
{
	GetAbilitySystemComponent()->RemoveLooseGameplayTag(TagsToRemove);
}

void ABaseCharacter::ApplyGEToTargetData(const FGameplayEffectSpecHandle& GESpec, const FGameplayAbilityTargetDataHandle& TargetData)
{
	for (TSharedPtr<FGameplayAbilityTargetData> Data : TargetData.Data)
	{
		Data->ApplyGameplayEffectSpec(*GESpec.Data.Get());
	}
}

void ABaseCharacter::SetHealthValues(float NewHealth, float NewMaxHealth)
{
	AbilitySystemComponent->ApplyModToAttribute(BaseAttributeSetComp->GetHealthAttribute(), EGameplayModOp::Override, NewHealth);
	AbilitySystemComponent->ApplyModToAttribute(BaseAttributeSetComp->GetMaxHealthAttribute(), EGameplayModOp::Override, NewMaxHealth);
}

void ABaseCharacter::SetManaValues(float NewMana, float NewMaxMana)
{
	AbilitySystemComponent->ApplyModToAttribute(BaseAttributeSetComp->GetManaAttribute(), EGameplayModOp::Override, NewMana);
	AbilitySystemComponent->ApplyModToAttribute(BaseAttributeSetComp->GetMaxManaAttribute(), EGameplayModOp::Override, NewMaxMana);
}

void ABaseCharacter::SetStaminaValues(float NewStamina, float NewMaxStamina)
{
	AbilitySystemComponent->ApplyModToAttribute(BaseAttributeSetComp->GetStaminaAttribute(), EGameplayModOp::Override, NewStamina);
	AbilitySystemComponent->ApplyModToAttribute(BaseAttributeSetComp->GetMaxStaminaAttribute(), EGameplayModOp::Override, NewMaxStamina);
}