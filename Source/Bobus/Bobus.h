// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EBobusAbilityInputID : uint8
{
	None		UMETA(DisplayName = "None"),

	Confirm		UMETA(DisplayName = "Confirm"),

	Cancel		UMETA(DisplayName = "Cancel"),

	// todo
	Jump		UMETA(DisplayName = "Jump"),

	// Debug
	Test		UMETA(DisplayName = "Test")

};