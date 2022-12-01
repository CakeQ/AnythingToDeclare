#pragma once

#include "CoreMinimal.h"
#include "../Fluff/Cargo/CargoDefinition.h"

#include "UObject/ObjectMacros.h"

#include "CargoManifest.generated.h"

enum class EGameplayTagModifier : uint8;

USTRUCT(BlueprintType)
struct FCargoManifestEntry
{
	GENERATED_BODY()
public:

	FCargoManifestEntry()
		: CargoType(nullptr)
		, DisplayWeightMultiplierPerUnit(0.0f)
		, TotalUnits(0)
	{
	}
	
	UPROPERTY(EditAnywhere)
	UCargoTypeDefinition* CargoType;

	UPROPERTY(EditAnywhere)
	FString DisplayName;

	UPROPERTY(EditAnywhere)
	float DisplayWeightMultiplierPerUnit;
	
	UPROPERTY(EditAnywhere)
	TArray<EGameplayTagModifier> Modifiers;
	
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