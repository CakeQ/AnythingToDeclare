#pragma once

#include "CoreMinimal.h"
#include "../Fluff/Cargo/CargoDefinition.h"

#include "UObject/ObjectMacros.h"

#include "CargoManifest.generated.h"

USTRUCT()
struct FCargoManifestEntry
{
	GENERATED_BODY()
public:
	UPROPERTY()
	UCargoTypeDefinition* CargoType;

	UPROPERTY()
	int32 TotalWeight;
};

USTRUCT()
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