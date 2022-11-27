// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#include "CustomsRequestDataMap.h"

#include "AnythingToDeclare/Fluff/Cargo/CargoCategoryDefinition.h"
#include "AnythingToDeclare/Fluff/Cargo/CargoDefinition.h"
#include "AnythingToDeclare/Fluff/Faction/FactionDefinition.h"
#include "AnythingToDeclare/Fluff/Location/LocationDefinition.h"
#include "AnythingToDeclare/Fluff/Location/RegionDefinition.h"
#include "AnythingToDeclare/Fluff/Location/SubLocationDefinition.h"
#include "AssetRegistry/AssetRegistryModule.h"

UCustomsRequestDataMap::UCustomsRequestDataMap()
{
}

void UCustomsRequestDataMap::PostLoad()
{
	Super::PostLoad();
	RegenerateDataLists();
}

void UCustomsRequestDataMap::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	RegenerateDataLists();
}

void UCustomsRequestDataMap::RegenerateDataLists()
{
	CargoWeights.Empty();
	ContrabandWeights.Empty();
	LocationWeights.Empty();
	SubLocationWeights.Empty();
	SelectableFactions.Empty();

	const FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	const IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();
	
	TArray<FAssetData> DataAssets;
	AssetRegistry.GetAssetsByPath(FName(DataPath.Path), DataAssets, true);

	for (const FAssetData& Asset : DataAssets)
	{
		if(UObject* AssetPtr = Asset.GetAsset())
		{
			if (UCargoTypeDefinition* CargoTypeDefinition = Cast<UCargoTypeDefinition>(AssetPtr))
			{
				if(CargoTypeDefinition != nullptr && CargoTypeDefinition->RandomlySelectable)
				{
					if(CargoTypeDefinition->IsIllegal)
					{
						ContrabandWeights.Add(CargoTypeDefinition, CargoTypeDefinition->SelectionWeight + (CargoTypeDefinition->Category != nullptr ? CargoTypeDefinition->Category->SelectionWeight : 0.0f));
					}
					else
					{
						CargoWeights.Add(CargoTypeDefinition, CargoTypeDefinition->SelectionWeight + (CargoTypeDefinition->Category != nullptr ? CargoTypeDefinition->Category->SelectionWeight : 0.0f));
					}
				}
			}
			else if(URegionDefinition* RegionDefinition = Cast<URegionDefinition>(AssetPtr))
			{
				if(RegionDefinition != nullptr)
				{
					RegionWeights.Add(RegionDefinition, RegionDefinition->PopularityModifier);
				}
			}
			else if(ULocationDefinition* LocationDefinition = Cast<ULocationDefinition>(AssetPtr))
			{
				if(LocationDefinition != nullptr && LocationDefinition->RandomlySelectable)
				{
					LocationWeights.Add(LocationDefinition, 
						LocationDefinition->PopularityModifier + (LocationDefinition->Region != nullptr ? LocationDefinition->Region->PopularityModifier : 0.0f));
				}
			}
			else if(USubLocationDefinition* SubLocationDefinition = Cast<USubLocationDefinition>(AssetPtr))
			{
				if(SubLocationDefinition != nullptr && SubLocationDefinition->RandomlySelectable)
				{
					SubLocationWeights.Add(SubLocationDefinition,
						SubLocationDefinition->PopularityModifier
						+ (SubLocationDefinition->Location != nullptr ? SubLocationDefinition->Location->PopularityModifier
							+ (SubLocationDefinition->Location->Region != nullptr ? SubLocationDefinition->Location->Region->PopularityModifier : 0.0f) : 0.0f));
				}
			}
			else if(UFactionDefinition* FactionDefinition = Cast<UFactionDefinition>(AssetPtr))
			{
				if(FactionDefinition != nullptr && FactionDefinition->RandomlySelectable)
				{
					SelectableFactions.Add(FactionDefinition, FactionDefinition->AppearanceWeight);
				}
			}
			else if(UShipClassDefinition* ShipClassDefinition = Cast<UShipClassDefinition>(AssetPtr))
			{
				if(ShipClassDefinition != nullptr && ShipClassDefinition->RandomlySelectable)
				{
					SelectableShipClasses.Add(ShipClassDefinition, ShipClassDefinition->AppearanceWeight);
				}
			}
		}
	}
}
