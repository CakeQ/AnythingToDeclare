// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#include "CustomsRequestDataMap.h"

#include "AnythingToDeclare/Fluff/Location/LocationDefinition.h"
#include "AnythingToDeclare/Fluff/Location/SubLocationDefinition.h"

UCustomsRequestDataMap::UCustomsRequestDataMap()
{
}

void UCustomsRequestDataMap::PostLoad()
{
	Super::PostLoad();

	LocationWeights.Empty();
	SubLocationWeights.Empty();
	
	for(ULocationDefinition* LocationDefinition : Locations)
	{
		LocationWeights.Add(LocationDefinition, LocationDefinition->PopularityModifier);
	}
	
	for(USubLocationDefinition* SubLocationDefinition : SubLocations)
	{
		SubLocationWeights.Add(SubLocationDefinition, SubLocationDefinition->PopularityModifier + (SubLocationDefinition->Location == nullptr ? SubLocationDefinition->Location->PopularityModifier : 0.0f));
	}
}
