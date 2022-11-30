// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#pragma once

#include "CoreMinimal.h"
#include "CustomsRequest.h"
#include "AnythingToDeclare/Character/CharacterDefinitionAsset.h"

class UGameplayTagContextAsset;
class UCustomsRequestDataMap;
class UDayDefinitionAsset;

namespace CustomsRequestsHelper
{
	void GenerateRequest(FCustomsRequest& InRequest, const UCustomsRequestDataMap* InDataMap, const UGameplayTagContextAsset* InGameplayTagContexts, const UDayDefinitionAsset* InDayDefinition);
	void GenerateCharacter(FCustomsRequest& InRequest, const UCustomsRequestDataMap* InDataMap, const UGameplayTagContextAsset* InGameplayTagContexts, const UDayDefinitionAsset* InDayDefinition);
	void GenerateCargoRoute(FCustomsRequest& InRequest, const UCustomsRequestDataMap* InDataMap, const UDayDefinitionAsset* InDayDefinition);
	void GenerateCargoManifest(FCustomsRequest& InRequest, const UCustomsRequestDataMap* InDataMap, const UGameplayTagContextAsset* InGameplayTagContexts, const UDayDefinitionAsset* InDayDefinition);
	
	void FillFromCharacterAppearance(FCustomsRequest& InRequest);
	
	template <typename DataType>
	DataType RandomEntryWithWeight(const TMap<DataType, float>& InData, const TArray<DataType>& EntriesToIgnore = TArray<DataType>())
	{
		float TotalWeight = 0.0f;
		for(const TPair<DataType, float>& Pair : InData)
		{
			if(!EntriesToIgnore.Contains(Pair.Key))
			{
				TotalWeight += Pair.Value;
			}
		}

		const float ChosenWeight = FMath::RandRange(0.0f, TotalWeight);
		float CurrentChosenWeight = 0.0f;
		
		for(const TPair<DataType, float>& Pair : InData)
		{
			if(EntriesToIgnore.Contains(Pair.Key))
			{
				continue;
			}
			
			CurrentChosenWeight += Pair.Value;
			if(ChosenWeight <= CurrentChosenWeight)
			{
				return Pair.Key;
			}
		}
		return DataType();
	}
}
