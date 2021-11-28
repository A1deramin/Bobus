// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Bobus/Bobus.h"
#include "BobusGameplayAbility.generated.h"

/**
 * Base ability class.
 */
UCLASS()
class BOBUS_API UBobusGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UBobusGameplayAbility();

	// Abilities will activate when the input is pressed.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	EBobusAbilityInputID AbilityInputID = EBobusAbilityInputID::None;

}; // class UBobusGameplayAbility
