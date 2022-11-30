﻿// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"
#include "UObject/Object.h"

#include "CustomsRequestDataMap.generated.h"

class UCharacterDefinitionAsset;
class UShipClassDefinition;
class UDataTable;
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
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	void RegenerateDataLists();

	void OnDataAssetLoaded(UObject* LoadedAsset);
	
	UPROPERTY(EditDefaultsOnly)
	UNameDefinitionMap* Names;

	UPROPERTY()
	TArray<UCargoTypeDefinition*> CargoTypes;

	UPROPERTY(EditDefaultsOnly)
	TArray<FDirectoryPath> DataPaths;

	UPROPERTY()
	TMap<UCargoTypeDefinition*, float> CargoWeights;
	
	UPROPERTY()
	TMap<UCargoTypeDefinition*, float> ContrabandWeights;
	
	UPROPERTY(EditDefaultsOnly)
	USubLocationDefinition* DefaultWorkLocation;
	
	UPROPERTY(EditDefaultsOnly)
	UCharacterDefinitionAsset* PlayerCharacter;
	
	UPROPERTY(EditDefaultsOnly)
	UDataTable* DefaultDialogue;
	
	UPROPERTY()
	TArray<URegionDefinition*> Regions;
	
	UPROPERTY()
	TArray<ULocationDefinition*> Locations;
	
	UPROPERTY()
	TArray<USubLocationDefinition*> SubLocations;

	UPROPERTY()
	TArray<UFactionDefinition*> Factions;

	UPROPERTY()
	TArray<UShipClassDefinition*> ShipClasses;
	
	UPROPERTY()
	TMap<URegionDefinition*, float> RegionWeights;
	
	UPROPERTY()
	TMap<ULocationDefinition*, float> LocationWeights;
	
	UPROPERTY()
	TMap<USubLocationDefinition*, float> SubLocationWeights;
	
	UPROPERTY()
	TMap<UFactionDefinition*, float> SelectableFactions;
	
	UPROPERTY()
	TMap<UShipClassDefinition*, float> SelectableShipClasses;
};
