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

	FCargoManifestEntry()
		: CargoType(nullptr)
		, TotalUnits(0)
	{
	}
	
	FCargoManifestEntry(UCargoTypeDefinition* InCargoType, const int32 InTotalUnits)
		: CargoType(InCargoType)
		, TotalUnits(InTotalUnits)
	{
	}
	
	UPROPERTY(EditAnywhere)
	UCargoTypeDefinition* CargoType;

	UPROPERTY(EditAnywhere)
	int32 TotalUnits;
};

USTRUCT(BlueprintType)
struct FCargoManifest
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	FString ShipName;

	UPROPERTY(EditAnywhere)
	FString OriginLocation;

	UPROPERTY(EditAnywhere)
	FString OriginSubLocation;

	UPROPERTY(EditAnywhere)
	FString DestinationLocation;

	UPROPERTY(EditAnywhere)
	FString DestinationSubLocation;

	UPROPERTY(EditAnywhere)
	TArray<FCargoManifestEntry> Cargo;
};