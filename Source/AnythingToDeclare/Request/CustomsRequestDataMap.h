// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"
#include "UObject/Object.h"

#include "CustomsRequestDataMap.generated.h"

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

	virtual void PostInitProperties() override;
	
	UPROPERTY(EditDefaultsOnly)
	UNameDefinitionMap* Names;

	UPROPERTY(EditDefaultsOnly)
	TArray<UCargoTypeDefinition*> CargoTypes;

	UPROPERTY(EditDefaultsOnly)
	USubLocationDefinition* DefaultWorkLocation;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<ULocationDefinition*> Locations;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<USubLocationDefinition*> SubLocations;

	UPROPERTY()
	TMap<ULocationDefinition*, float> LocationWeights;
	
	UPROPERTY()
	TMap<USubLocationDefinition*, float> SubLocationWeights;
};
