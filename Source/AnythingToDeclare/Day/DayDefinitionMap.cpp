// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/


#include "DayDefinitionMap.h"

#include "DayDefinition.h"
#include "Loader.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"

UDayDefinitionMap::UDayDefinitionMap()
{
}

void UDayDefinitionMap::PostLoad()
{
	Super::PostLoad();
	RegenerateDataLists();
}

void UDayDefinitionMap::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	RegenerateDataLists();
}

void UDayDefinitionMap::RegenerateDataLists()
{
	Days.Empty();
	
	const FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	const IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();
	
	TArray<FAssetData> DataAssets;
	AssetRegistry.GetAssetsByPath(FName(DaysFolder.Path), DataAssets, true);

	for (const FAssetData& Asset : DataAssets)
	{
		FLoader::Load<UDayDefinitionAsset>(Asset.ToSoftObjectPath(), [this](const UDayDefinitionAsset& InLoadedAsset)
		{
			OnDayAssetLoaded(&InLoadedAsset);
		});
	}
}

void UDayDefinitionMap::OnDayAssetLoaded(const UDayDefinitionAsset* LoadedAsset)
{
	Days.Add(LoadedAsset);
}

const UDayDefinitionAsset* UDayDefinitionMap::FindDayNumber(const int32 InDayNumber) const
{
	for(const UDayDefinitionAsset* Definition : Days)
	{
		if(Definition != nullptr && Definition->DayNumber == InDayNumber)
		{
			return Definition;
		}
	}
	return nullptr;
}
