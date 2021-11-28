#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "BobusCharacterBase.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UMotionControllerComponent;
class UAnimMontage;
class USoundBase;

/**
* The base Character class.	Everything with an ASC will inherit from this class.
*/
UCLASS(config=Game)
class ABobusCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABobusCharacterBase();

	// Implement IAbilitySystemInterface
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;


protected:

	virtual void BeginPlay() override;

	// Lives on the PlayerState or here if character doesn't have a PlayerState
	class UBobusAbilitySystemComponent* AbilitySystemComponent;
	class UBobusAttributeSetBase* AttributeSet;


	// Default abilities for this Character.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Abilities)
	TArray<TSubclassOf<class UBobusGameplayAbility>> CharacterAbilities;

	// Default attributes for this Character.
	// This is an instant GE that overrides the values for attributes.
	// Will get reset on spawn.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Abilities)
	TSubclassOf<class UGameplayEffect> DefaultAttriubutes;

	// Applied one time on startup
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Abilities)
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

	// Grant abilities on the Server. The Ability Specs will be replicated to the owning client.
	virtual void AddCharacterAbilities();
	
	// Initialize the Character's attributes. Run on Server and Client.
	virtual void InitializeAttributes();
	
	virtual void AddStartupEffects();

}; // class ABobusCharacterBase

