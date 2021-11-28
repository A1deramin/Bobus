// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "BobusPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class BOBUS_API ABobusPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	ABobusPlayerState();

	// Implement IAbilitySystemInterface
	class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	class UBobusAttributeSetBase* GetAttributeSetBase() const;
	

protected:

	UPROPERTY()
	class UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	class UBobusAttributeSetBase* AttributeSetBase;

}; // class ABobusPlayerState
