﻿// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#include "CustomsRequestDataMap.h"

#include "AnythingToDeclare/Fluff/Cargo/CargoDefinition.h"
#include "AnythingToDeclare/Fluff/Faction/FactionDefinition.h"
#include "AnythingToDeclare/Fluff/Location/LocationDefinition.h"
#include "AnythingToDeclare/Fluff/Location/RegionDefinition.h"
#include "AnythingToDeclare/Fluff/Location/SubLocationDefinition.h"

UCustomsRequestDataMap::UCustomsRequestDataMap()
{
}

void UCustomsRequestDataMap::PostLoad()
{
	Super::PostLoad();
	
	SelectableCargoTypes.Empty();
	SelectableContrabandTypes.Empty();
	LocationWeights.Empty();
	SubLocationWeights.Empty();
	SelectableFactions.Empty();
	
	for(UCargoTypeDefinition* CargoTypeDefinition : CargoTypes)
	{
		if(CargoTypeDefinition->RandomlySelectable)
		{
			if(CargoTypeDefinition->IsIllegal)
			{
				SelectableContrabandTypes.Add(CargoTypeDefinition);
			}
			else
			{
				SelectableCargoTypes.Add(CargoTypeDefinition);
			}
		}
	}
	
	for(URegionDefinition* RegionDefinition : Regions)
	{
		RegionWeights.Add(RegionDefinition, RegionDefinition->PopularityModifier);
	}
	
	for(ULocationDefinition* LocationDefinition : Locations)
	{
		if(LocationDefinition->RandomlySelectable)
		{
			LocationWeights.Add(LocationDefinition, 
				LocationDefinition->PopularityModifier + (LocationDefinition->Region != nullptr ? LocationDefinition->Region->PopularityModifier : 0.0f));
		}
	}
	
	for(USubLocationDefinition* SubLocationDefinition : SubLocations)
	{
		if(SubLocationDefinition->RandomlySelectable)
		{
			SubLocationWeights.Add(SubLocationDefinition,
				SubLocationDefinition->PopularityModifier
				+ (SubLocationDefinition->Location != nullptr ? SubLocationDefinition->Location->PopularityModifier
					+ (SubLocationDefinition->Location->Region != nullptr ? SubLocationDefinition->Location->Region->PopularityModifier : 0.0f) : 0.0f));
		}
	}
	
	for(UFactionDefinition* FactionDefinition : Factions)
	{
		if(FactionDefinition->RandomlySelectable)
		{
			SelectableFactions.Add(FactionDefinition, FactionDefinition->AppearanceWeight);
		}
	}
	
	for(UShipClassDefinition* ShipClassDefinition : ShipClasses)
	{
		if(ShipClassDefinition->RandomlySelectable)
		{
			SelectableShipClasses.Add(ShipClassDefinition, ShipClassDefinition->AppearanceWeight);
		}
	}
}
