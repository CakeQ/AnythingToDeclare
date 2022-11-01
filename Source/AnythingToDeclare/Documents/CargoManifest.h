#pragma once

#include "CoreMinimal.h"
#include "../Fluff/Cargo/CargoDefinition.h"

#include "UObject/ObjectMacros.h"

#include "CargoManifest.generated.h"

USTRUCT(BlueprintType)
struct FCargoManifestEntry
{
	GENERATED_BODY()
public:
	UPROPERTY()
	UCargoTypeDefinition* CargoType;

	UPROPERTY()
	int32 TotalWeight;
};

USTRUCT(BlueprintType)
struct FCargoManifest
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FString ShipName;

	UPROPERTY()
	FString OriginPlanet;

	UPROPERTY()
	FString DestinationPlanet;

	UPROPERTY()
	TArray<FCargoManifestEntry> Cargo;
};