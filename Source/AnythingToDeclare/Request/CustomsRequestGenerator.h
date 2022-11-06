// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#pragma once

#include "CoreMinimal.h"
#include "CustomsRequest.h"
#include "AnythingToDeclare/Character/CharacterDefinitionAsset.h"

class UCustomsRequestDataMap;
class UDayDefinitionAsset;

namespace CustomsRequestsHelper
{
	void GenerateRequest(FCustomsRequest& InRequest, const UCustomsRequestDataMap* InDataMap, const UDayDefinitionAsset* InDayDefinition);
	void GenerateCargoRoute(FCustomsRequest& InRequest, const UCustomsRequestDataMap* InDataMap, const UDayDefinitionAsset* InDayDefinition);
	void GenerateCargoManifest(FCargoManifest& InManifest, const UCustomsRequestDataMap* InDataMap, const UDayDefinitionAsset* InDayDefinition, const
	                           USubLocationDefinition* Origin, const USubLocationDefinition* Destination);
	void GenerateCargoFromParameters(FCargoManifest& InManifest, const TMap<ECustomsRequestModifier, float>& RequestModifiers, const USubLocationDefinition*
	                                 Origin, const USubLocationDefinition* Destination);
	
	void FillFromCharacterAppearance(FCustomsRequest& InRequest);
	
	template <typename DataType>
	DataType RandomEntryWithWeight(const TMap<DataType, float>& InData)
	{
		float TotalWeight = 0.0f;
		for(const TPair<DataType, float>& Pair : InData)
		{
			TotalWeight += Pair.Value;
		}

		const float ChosenWeight = FMath::RandRange(0.0f, TotalWeight);
		float CurrentChosenWeight = 0.0f;
		
		for(const TPair<DataType, float>& Pair : InData)
		{
			CurrentChosenWeight += Pair.Value;
			if(ChosenWeight <= CurrentChosenWeight)
			{
				return Pair.Key;
			}
		}
		return DataType();
	}
}
