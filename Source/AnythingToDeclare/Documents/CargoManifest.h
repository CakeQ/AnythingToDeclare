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
	UPROPERTY(EditAnywhere)
	UCargoTypeDefinition* CargoType;

	UPROPERTY(EditAnywhere)
	int32 TotalWeight;
};

USTRUCT(BlueprintType)
struct FCargoManifest
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	FString ShipName;

	UPROPERTY(EditAnywhere)
	FString OriginPlanet;

	UPROPERTY(EditAnywhere)
	FString DestinationPlanet;

	UPROPERTY(EditAnywhere)
	TArray<FCargoManifestEntry> Cargo;
};