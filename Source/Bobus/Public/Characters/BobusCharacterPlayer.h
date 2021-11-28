// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BobusCharacterBase.h"
#include "BobusCharacterPlayer.generated.h"

/**
 * Character controlled by the player or AI.
 */
UCLASS()
class BOBUS_API ABobusCharacterPlayer : public ABobusCharacterBase
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** Dumb hitboxes to make server side rewind easier (for educational purposes) */
	UPROPERTY(VisibleAnywhere, Category = Hit)
	UCapsuleComponent* BodyHit;
	UPROPERTY(VisibleAnywhere, Category = Hit)
	class USphereComponent* HeadHit;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USceneComponent* FP_MuzzleLocation;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;		

	// Server only
	virtual void PossessedBy(AController* NewController) override;

public:
	ABobusCharacterPlayer();

protected:
	virtual void BeginPlay() override;

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	// Clients only
	virtual void OnRep_PlayerState() override;
	virtual void OnRep_Controller() override;

	// Called from both SetupPlayerInputComponent and OnRep_PlayerState because of a potential race condition where the PlayerController might
	// call ClientRestart which calls SetupPlayerInputComponent before the PlayerState is repped to the client so the PlayerState would be null in SetupPlayerInputComponent.
	// Conversely, the PlayerState might be repped before the PlayerController calls ClientRestart so the Actor's InputComponent would be null in OnRep_PlayerState.
	void BindASCInput();


public:
	
	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector GunOffset;

protected:
	// APawn interface

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	// End of APawn interface
public:

	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

}; // class ABobusCharacterPlayer
