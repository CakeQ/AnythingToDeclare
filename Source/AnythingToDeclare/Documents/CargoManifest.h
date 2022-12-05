#pragma once

#include "CoreMinimal.h"
#include "../Fluff/Cargo/CargoDefinition.h"

#include "UObject/ObjectMacros.h"

#include "CargoManifest.generated.h"

enum class EGameplayTagModifier : uint8;

USTRUCT()
struct FCargoManifestEntry
{
	GENERATED_BODY()
public:

	FCargoManifestEntry()
		: CargoType(nullptr)
		, DisplayedCargoType(nullptr)
		, DisplayWeightMultiplierPerUnit(0.0f)
		, TotalUnits(0)
	{
	}

	UPROPERTY()
	UCargoTypeDefinition* CargoType;

	UPROPERTY()
	UCargoTypeDefinition* DisplayedCargoType;

	UPROPERTY()
	FString DisplayName;

	UPROPERTY()
	float DisplayWeightMultiplierPerUnit;
	
	UPROPERTY()
	TArray<EGameplayTagModifier> Modifiers;
	
	UPROPERTY()
	int32 TotalUnits;
};

USTRUCT()
struct FCargoManifest
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FString ShipName;

	UPROPERTY()
	FString OriginLocation;

	UPROPERTY()
	FString OriginSubLocation;

	UPROPERTY()
	FString DestinationLocation;

	UPROPERTY()
	FString DestinationSubLocation;

	UPROPERTY()
	TArray<FCargoManifestEntry> Cargo;
};