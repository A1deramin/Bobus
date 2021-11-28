// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BobusCharacterPlayer.h"
#include "Weapons/BobusProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Player/BobusPlayerState.h"
#include "Characters/Abilities/BobusAbilitySystemComponent.h"
#include "Bobus/Bobus.h"
#include "MotionControllerComponent.h"

ABobusCharacterPlayer::ABobusCharacterPlayer()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	//bReplicates = true;
	SetReplicateMovement(true);

	NetUpdateFrequency = 1.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	// Configure a mesh component that will be used when being viewed from a '3d person' view
	GetMesh()->SetOwnerNoSee(true);

	BodyHit = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Body Hit"));
	BodyHit->SetCapsuleHalfHeight(68.5f);
	BodyHit->SetCapsuleRadius(30.f);
	BodyHit->SetRelativeLocation(FVector(0, 0, -30.f));

	HeadHit = CreateDefaultSubobject<USphereComponent>(TEXT("Head Hit"));
	HeadHit->SetSphereRadius(22.f);
	HeadHit->SetupAttachment(BodyHit);
	HeadHit->SetRelativeLocation(FVector(0, 0, BodyHit->GetUnscaledCapsuleHalfHeight() + HeadHit->GetUnscaledSphereRadius()));
	



	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(false);			// otherwise won't be visible in the multiplayer
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

}

void ABobusCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

	Mesh1P->SetHiddenInGame(false, true);

}
void ABobusCharacterPlayer::BindASCInput()
{
	if (InputComponent && AbilitySystemComponent)
	{
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent,
			FGameplayAbilityInputBinds(FString("ConfirmTarget"), FString("CancelTarget"), FString("EBobusAbilityInputID"),
				static_cast<int32>(EBobusAbilityInputID::Confirm), static_cast<int32>(EBobusAbilityInputID::Cancel)));
	}
}

void ABobusCharacterPlayer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ABobusCharacterPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABobusCharacterPlayer::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	
	BindASCInput();
}

void ABobusCharacterPlayer::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ABobusCharacterPlayer::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

// Server only
void ABobusCharacterPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	ABobusPlayerState* PS = GetPlayerState<ABobusPlayerState>();
	if (PS)
	{
		AbilitySystemComponent = Cast<UBobusAbilitySystemComponent>(PS->GetAbilitySystemComponent());

		AbilitySystemComponent->InitAbilityActorInfo(PS, this);
		
		AttributeSet = PS->GetAttributeSetBase();

		InitializeAttributes();

		AddStartupEffects();

		AddCharacterAbilities();

	}
}
// Clients only
void ABobusCharacterPlayer::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	ABobusPlayerState* PS = GetPlayerState<ABobusPlayerState>();
	if (PS)
	{	// Set ASC for clients
		AbilitySystemComponent = Cast<UBobusAbilitySystemComponent>(PS->GetAbilitySystemComponent());

		AbilitySystemComponent->InitAbilityActorInfo(PS, this);

		AttributeSet = PS->GetAttributeSetBase();

		BindASCInput();

		InitializeAttributes();
	}
}
void ABobusCharacterPlayer::OnRep_Controller()
{
	Super::OnRep_Controller();
}

