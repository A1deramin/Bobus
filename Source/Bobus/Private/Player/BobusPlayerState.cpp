// Fill out your copyright notice in the Description page of Project Settings.
#include "Player/BobusPlayerState.h"
#include "Characters/Abilities/BobusAttributeSetBase.h" 
#include "Characters/Abilities/BobusAbilitySystemComponent.h"

ABobusPlayerState::ABobusPlayerState()
{	
	// Keep ASC within PlayerState, need persistence of GA and GE between spawns.
	AbilitySystemComponent = CreateDefaultSubobject<UBobusAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	// Replicated by default
	AttributeSetBase = CreateDefaultSubobject<UBobusAttributeSetBase>(TEXT("AttributeSetBase"));
	
	// Should be same as the Charecter.
	// Default is too low for abilities
	// Keep very low for debug and test purposes.
	NetUpdateFrequency = 1.f;

}

UAbilitySystemComponent* ABobusPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UBobusAttributeSetBase* ABobusPlayerState::GetAttributeSetBase() const
{
	return AttributeSetBase;
}
