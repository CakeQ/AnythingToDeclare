#pragma once

#include "CoreMinimal.h"
#include "LinkedDataTypes.h"

#include "CargoManifest.generated.h"

class USubLocationDefinition;
enum class EGameplayTagModifier : uint8;

USTRUCT()
struct FCargoManifestEntry
{
	GENERATED_BODY()
public:

	FCargoManifestEntry()
		: DisplayName()
		, DisplayWeightMultiplier()
		, DisplayValueMultiplier()
		, TotalUnits()
		, Modifiers()
	{
	}

	UPROPERTY()
	FLinkedDataString DisplayName;

	UPROPERTY()
	FLinkedDataFloat DisplayWeightMultiplier;
	
	UPROPERTY()
	FLinkedDataFloat DisplayValueMultiplier;
	
	UPROPERTY()
	FLinkedDataInt TotalUnits;
	
	UPROPERTY()
	TArray<EGameplayTagModifier> Modifiers;
};

USTRUCT()
struct FCargoManifest
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FString ShipName;

	UPROPERTY()
	FLinkedDataString OriginLocation;

	UPROPERTY()
	FLinkedDataString OriginSubLocation;

	UPROPERTY()
	FLinkedDataString DestinationLocation;

	UPROPERTY()
	FLinkedDataString DestinationSubLocation;

	UPROPERTY()
	TArray<FCargoManifestEntry> Cargo;
};