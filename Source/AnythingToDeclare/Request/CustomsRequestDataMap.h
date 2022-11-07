// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"
#include "UObject/Object.h"

#include "CustomsRequestDataMap.generated.h"

class URegionDefinition;
class UFactionDefinition;
class UCargoTypeDefinition;
class UDayDefinitionAsset;
class ULocationDefinition;
class UNameDefinitionMap;
class USubLocationDefinition;

/**
 * 
 */
UCLASS()
class ANYTHINGTODECLARE_API UCustomsRequestDataMap : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UCustomsRequestDataMap();
	
	virtual void PostLoad() override;
	
	UPROPERTY(EditDefaultsOnly)
	UNameDefinitionMap* Names;

	UPROPERTY(EditDefaultsOnly)
	TArray<UCargoTypeDefinition*> CargoTypes;

	UPROPERTY()
	TArray<UCargoTypeDefinition*> SelectableCargoTypes;
	
	UPROPERTY()
	TArray<UCargoTypeDefinition*> SelectableContrabandTypes;
	
	UPROPERTY(EditDefaultsOnly)
	USubLocationDefinition* DefaultWorkLocation;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<URegionDefinition*> Regions;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<ULocationDefinition*> Locations;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<USubLocationDefinition*> SubLocations;

	UPROPERTY(EditDefaultsOnly)
	TArray<UFactionDefinition*> Factions;
	
	UPROPERTY()
	TMap<UFactionDefinition*, float> SelectableFactions;
	
	UPROPERTY()
	TMap<URegionDefinition*, float> RegionWeights;
	
	UPROPERTY()
	TMap<ULocationDefinition*, float> LocationWeights;
	
	UPROPERTY()
	TMap<USubLocationDefinition*, float> SubLocationWeights;
};
