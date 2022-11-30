// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#include "CustomsRequestDataMap.h"

#include "Loader.h"
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
	RegionWeights.Empty();
	LocationWeights.Empty();
	SubLocationWeights.Empty();
	SelectableFactions.Empty();
	SelectableShipClasses.Empty();
	
	CargoTypes.Empty();
	Regions.Empty();
	Locations.Empty();
	SubLocations.Empty();
	Factions.Empty();
	ShipClasses.Empty();
	
	const FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	const IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();
	
	TArray<FAssetData> DataAssets;
	TArray<FName> PathsToLoad;
	for(auto& [Path] : DataPaths)
	{
		PathsToLoad.Add(FName(Path));
	}
	AssetRegistry.GetAssetsByPaths(PathsToLoad, DataAssets, true);

	for (const FAssetData& Asset : DataAssets)
	{
		FLoader::Load<UObject>(Asset.ToSoftObjectPath(), [this](UObject& InLoadedAsset)
		{
			OnDataAssetLoaded(&InLoadedAsset);
		});
	}
}

void UCustomsRequestDataMap::OnDataAssetLoaded(UObject* LoadedAsset)
{
	if (UCargoTypeDefinition* CargoTypeDefinition = Cast<UCargoTypeDefinition>(LoadedAsset))
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
			CargoTypes.Add(CargoTypeDefinition);
		}
	}
	else if(URegionDefinition* RegionDefinition = Cast<URegionDefinition>(LoadedAsset))
	{
		if(RegionDefinition != nullptr)
		{
			RegionWeights.Add(RegionDefinition, RegionDefinition->PopularityModifier);
			Regions.Add(RegionDefinition);
		}
	}
	else if(ULocationDefinition* LocationDefinition = Cast<ULocationDefinition>(LoadedAsset))
	{
		if(LocationDefinition != nullptr && LocationDefinition->RandomlySelectable)
		{
			LocationWeights.Add(LocationDefinition, 
				LocationDefinition->PopularityModifier + (LocationDefinition->Region != nullptr ? LocationDefinition->Region->PopularityModifier : 0.0f));
			Locations.Add(LocationDefinition);
		}
	}
	else if(USubLocationDefinition* SubLocationDefinition = Cast<USubLocationDefinition>(LoadedAsset))
	{
		if(SubLocationDefinition != nullptr && SubLocationDefinition->RandomlySelectable)
		{
			SubLocationWeights.Add(SubLocationDefinition,
				SubLocationDefinition->PopularityModifier
				+ (SubLocationDefinition->Location != nullptr ? SubLocationDefinition->Location->PopularityModifier
					+ (SubLocationDefinition->Location->Region != nullptr ? SubLocationDefinition->Location->Region->PopularityModifier : 0.0f) : 0.0f));
			SubLocations.Add(SubLocationDefinition);
		}
	}
	else if(UFactionDefinition* FactionDefinition = Cast<UFactionDefinition>(LoadedAsset))
	{
		if(FactionDefinition != nullptr)
		{
			if(FactionDefinition->RandomlySelectable)
			{
				SelectableFactions.Add(FactionDefinition, FactionDefinition->AppearanceWeight);
			}
			Factions.Add(FactionDefinition);
		}
	}
	else if(UShipClassDefinition* ShipClassDefinition = Cast<UShipClassDefinition>(LoadedAsset))
	{
		if(ShipClassDefinition != nullptr)
		{
			if(ShipClassDefinition->RandomlySelectable)
			{
				SelectableShipClasses.Add(ShipClassDefinition, ShipClassDefinition->AppearanceWeight);
			}
			ShipClasses.Add(ShipClassDefinition);
		}
	}
}
