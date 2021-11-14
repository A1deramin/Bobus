#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BobusCharacterBase.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UMotionControllerComponent;
class UAnimMontage;
class USoundBase;

UCLASS(config=Game)
class ABobusCharacterBase : public ACharacter
{
	GENERATED_BODY()


public:
	ABobusCharacterBase();

protected:
	virtual void BeginPlay() override;

public:




protected:
	


protected:


public:

};

