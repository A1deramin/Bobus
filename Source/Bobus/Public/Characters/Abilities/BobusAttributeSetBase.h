// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BobusAttributeSetBase.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * Holds base Player or AI controlled Character stats.
 */
UCLASS()
class BOBUS_API UBobusAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()

public:
	UBobusAttributeSetBase();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProperty) const override;

	// Current Health, when 0 we expect owner to die unless prevented by an ability. Capped by MaxHealth.
	// Positive changes can directly use this.
	// Negative changes to Health should go through Damage meta attribute.
	UPROPERTY(BlueprintReadOnly, Category = Health, ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UBobusAttributeSetBase, Health)

	// MaxHealth is its own attribute since GameplayEffects may modify it
	UPROPERTY(BlueprintReadOnly, Category = Health, ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UBobusAttributeSetBase, MaxHealth)

	// Health regen rate will passively increase Health every second
	UPROPERTY(BlueprintReadOnly, Category = Health, ReplicatedUsing = OnRep_HealthRegenRate)
	FGameplayAttributeData HealthRegenRate;
	ATTRIBUTE_ACCESSORS(UBobusAttributeSetBase, HealthRegenRate)
	
	// Current stamina, used to execute special abilities. Capped by MaxStamina.
	UPROPERTY(BlueprintReadOnly, Category = Stamina, ReplicatedUsing = OnRep_Stamina)
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UBobusAttributeSetBase, Stamina)

	// MaxStamina is its own attribute since GameplayEffects may modify it
	UPROPERTY(BlueprintReadOnly, Category = Stamina, ReplicatedUsing = OnRep_MaxStamina)
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UBobusAttributeSetBase, MaxStamina)

	// Stamina regen rate will passively increase Stamina every second
	UPROPERTY(BlueprintReadOnly, Category = Stamina, ReplicatedUsing = OnRep_StaminaRegenRate)
	FGameplayAttributeData StaminaRegenRate;
	ATTRIBUTE_ACCESSORS(UBobusAttributeSetBase, StaminaRegenRate)
	
	// Armor reduces the amount of damage done by attackers
	UPROPERTY(BlueprintReadOnly, Category = Armor, ReplicatedUsing = OnRep_Armor)
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UBobusAttributeSetBase, Armor)

	// Damage is a meta attribute used by the DamageExecution to calculate final damage, which then turns into -Health
	// Temporary value that only exists on the Server. Not replicated.
	UPROPERTY(BlueprintReadOnly, Category = Damage)
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UBobusAttributeSetBase, Damage)
	
	// MoveSpeed affects how fast characters can move.
	UPROPERTY(BlueprintReadOnly, Category = MoveSpeed, ReplicatedUsing = OnRep_MoveSpeed)
	FGameplayAttributeData MoveSpeed;
	ATTRIBUTE_ACCESSORS(UBobusAttributeSetBase, MoveSpeed)

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

protected:

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);

	UFUNCTION()
	virtual void OnRep_HealthRegenRate(const FGameplayAttributeData& OldHealthRegenRate);

	UFUNCTION()
	virtual void OnRep_Stamina(const FGameplayAttributeData& OldStamina);

	UFUNCTION()
	virtual void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina);

	UFUNCTION()
	virtual void OnRep_StaminaRegenRate(const FGameplayAttributeData& OldStaminaRegenRate);

	UFUNCTION()
	virtual void OnRep_Armor(const FGameplayAttributeData& OldArmor);

	UFUNCTION()
	virtual void OnRep_MoveSpeed(const FGameplayAttributeData& OldMoveSpeed);
	
}; // class UBobusAttributeSetBase
