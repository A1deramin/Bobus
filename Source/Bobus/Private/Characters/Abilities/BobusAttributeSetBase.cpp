// Fill out your copyright notice in the Description page of Project Settings.
#include "Characters/Abilities/BobusAttributeSetBase.h"
#include "GameplayEffectExtension.h"
#include "Characters/BobusCharacterBase.h"
#include "GameplayEffect.h"
#include "Net/UnrealNetwork.h"

UBobusAttributeSetBase::UBobusAttributeSetBase()
{

}
void UBobusAttributeSetBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const 
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UBobusAttributeSetBase, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBobusAttributeSetBase, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBobusAttributeSetBase, HealthRegenRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBobusAttributeSetBase, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBobusAttributeSetBase, MaxStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBobusAttributeSetBase, StaminaRegenRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBobusAttributeSetBase, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBobusAttributeSetBase, MoveSpeed, COND_None, REPNOTIFY_Always);
}

void UBobusAttributeSetBase::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp<float>(NewValue, 0.f, GetMaxHealth());
	}

	if (Attribute == GetStaminaAttribute())
	{
		NewValue = FMath::Clamp<float>(NewValue, 0.f, GetMaxStamina());
	}

	if (Attribute == GetMoveSpeedAttribute())
	{
		NewValue = FMath::Clamp<float>(NewValue, 100, 100);
	}

}

void UBobusAttributeSetBase::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
	const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();
	FGameplayTagContainer SpecAssetTags;
	Data.EffectSpec.GetAllAssetTags(SpecAssetTags);

	// Target Data
	AActor* TargetActor = nullptr;
	AController* TargetController = nullptr;
	ABobusCharacterBase* TargetCharacter = nullptr;
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		TargetCharacter = Cast<ABobusCharacterBase>(TargetActor);
	}

	// Source Data
	AActor* SourceActor = nullptr;
	AController* SourceController = nullptr;
	ABobusCharacterBase* SourceCharacter = nullptr;
	if (Source && Source->AbilityActorInfo.IsValid() && Source->AbilityActorInfo->AvatarActor.IsValid())
	{
		SourceActor = Source->AbilityActorInfo->AvatarActor.Get();
		SourceController = Source->AbilityActorInfo->PlayerController.Get();
		if (!SourceController && SourceActor)
		{
			if (auto* Pawn = Cast<APawn>(SourceActor))
			{
				SourceController = Pawn->GetController();
			}
		}
		
		if (SourceController)
		{
			SourceCharacter = Cast<ABobusCharacterBase>(SourceController->GetPawn());
		}
		else {
			SourceCharacter = Cast<ABobusCharacterBase>(SourceActor);
		}

		if (Context.GetEffectCauser())
		{
			SourceActor = Context.GetEffectCauser();
		}
	}

	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		//todo apply damage
	}

}







void UBobusAttributeSetBase::OnRep_Health(const FGameplayAttributeData& OldHelath)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBobusAttributeSetBase, Health, OldHelath);
}

void UBobusAttributeSetBase::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBobusAttributeSetBase, MaxHealth, OldMaxHealth);
}

void UBobusAttributeSetBase::OnRep_HealthRegenRate(const FGameplayAttributeData& OldHealthRegenRate)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBobusAttributeSetBase, HealthRegenRate, OldHealthRegenRate);
}

void UBobusAttributeSetBase::OnRep_Stamina(const FGameplayAttributeData& OldStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBobusAttributeSetBase, Stamina, OldStamina);
}

void UBobusAttributeSetBase::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBobusAttributeSetBase, MaxStamina, OldMaxStamina);
}

void UBobusAttributeSetBase::OnRep_StaminaRegenRate(const FGameplayAttributeData& OldStaminaRegenRate)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBobusAttributeSetBase, StaminaRegenRate, OldStaminaRegenRate);
}

void UBobusAttributeSetBase::OnRep_Armor(const FGameplayAttributeData& OldArmor)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBobusAttributeSetBase, Armor, OldArmor);
}

void UBobusAttributeSetBase::OnRep_MoveSpeed(const FGameplayAttributeData& OldMoveSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBobusAttributeSetBase, MoveSpeed, OldMoveSpeed);
}
