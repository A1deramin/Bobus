// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/BobusCharacterBase.h"
#include "Characters/Abilities/BobusAbilitySystemComponent.h"
#include "Characters/Abilities/BobusAttributeSetBase.h"
#include "Characters/Abilities/BobusGameplayAbility.h"

//////////////////////////////////////////////////////////////////////////
// ABobusCharacterBase

ABobusCharacterBase::ABobusCharacterBase()
{
	

	
}

UAbilitySystemComponent* ABobusCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ABobusCharacterBase::BeginPlay()
{
	Super::BeginPlay();

}

void ABobusCharacterBase::AddCharacterAbilities()
{
	if(GetLocalRole() != ROLE_Authority || !AbilitySystemComponent)
	{
		return;
	}

	for (auto& StartupAbility : CharacterAbilities)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility, 1, static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));
	}
}
void ABobusCharacterBase::InitializeAttributes()
{
	if (!AbilitySystemComponent || !DefaultAttriubutes)
	{
		return;
	}
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle GESpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttriubutes, 1, EffectContext);

	if (GESpecHandle.IsValid())
	{
		FActiveGameplayEffectHandle	ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*GESpecHandle.Data.Get());
	}
}

void ABobusCharacterBase::AddStartupEffects()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent)
	{
		return;
	}
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (auto& GameplayEffect : StartupEffects)
	{
		FGameplayEffectSpecHandle GESpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, 1, EffectContext);
		if (GESpecHandle.IsValid())
		{
			//TODO: text and compare
			AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*GESpecHandle.Data.Get(), AbilitySystemComponent);
		}
	}
}







