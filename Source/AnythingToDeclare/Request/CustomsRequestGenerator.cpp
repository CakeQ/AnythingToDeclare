// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#include "CustomsRequestGenerator.h"

#include "CustomsRequestDataMap.h"
#include "AnythingToDeclare/Character/CharacterDefinitionAsset.h"
#include "AnythingToDeclare/Day/DayDefinition.h"
#include "AnythingToDeclare/Fluff/Cargo/CargoCategoryDefinition.h"
#include "AnythingToDeclare/Fluff/Faction/FactionDefinition.h"
#include "AnythingToDeclare/Fluff/Location/LocationDefinition.h"
#include "AnythingToDeclare/Fluff/Location/SubLocationDefinition.h"
#include "AnythingToDeclare/Fluff/Names/NameDefinitionMap.h"

namespace
{
	namespace CustomsRequestsHelperPrivates
	{
		const FString CustomsRequestHelperDataTableContextString = TEXT("CustomsRequestsHelper");
	}
}

void CustomsRequestsHelper::GenerateRequest(FCustomsRequest& InRequest, const UCustomsRequestDataMap* InDataMap, const UDayDefinitionAsset* InDayDefinition)
{
	FillFromCharacterAppearance(InRequest);
	if(InRequest.Ship == nullptr)
	{
		InRequest.Ship = RandomEntryWithWeight(InDataMap->SelectableShipClasses);
	}
	if(InRequest.Faction == nullptr)
	{
		InRequest.Faction = RandomEntryWithWeight(InDataMap->SelectableFactions);
	}
	GenerateCargoRoute(InRequest, InDataMap, InDayDefinition);
	GenerateCargoManifest(InRequest, InDataMap, InDayDefinition);
}

void CustomsRequestsHelper::GenerateCargoRoute(FCustomsRequest& InRequest, const UCustomsRequestDataMap* InDataMap,
	const UDayDefinitionAsset* InDayDefinition)
{
	if(InRequest.RequestType == ECustomsRequestType::None)
	{
		InRequest.RequestType = RandomEntryWithWeight(InDayDefinition->CustomsRequestTypeWeight);
	}

	TArray<USubLocationDefinition*> AlreadyUsedLocations;
	if(InRequest.OriginLocation == nullptr)
	{
		if(InRequest.RequestType == ECustomsRequestType::Outbound)
		{
			InRequest.OriginLocation = InDayDefinition->WorkLocationOverride != nullptr ? InDayDefinition->WorkLocationOverride : InDataMap->DefaultWorkLocation;
		}
		else
		{
			InRequest.OriginLocation = RandomEntryWithWeight(InDataMap->SubLocationWeights);
		}
		AlreadyUsedLocations.Add(InRequest.OriginLocation);
	}

	if(InRequest.DestinationLocation == nullptr)
	{
		if(InRequest.RequestType == ECustomsRequestType::Inbound)
		{
			InRequest.DestinationLocation = InDayDefinition->WorkLocationOverride != nullptr ? InDayDefinition->WorkLocationOverride : InDataMap->DefaultWorkLocation;
		}
		else
		{
			if(FMath::RandBool() && InRequest.OriginLocation != nullptr && !InRequest.OriginLocation->SuppliedCargoTypes.IsEmpty())
			{
				TMap<USubLocationDefinition*, float> MutuallyBeneficialLocations;
				for(const TPair<USubLocationDefinition*, float>& Location : InDataMap->SubLocationWeights)
				{
					if(Location.Key != nullptr)
					{
						for(UCargoTypeDefinition* CargoType : Location.Key->DemandedCargoTypes)
						{
							if(InRequest.OriginLocation->SuppliedCargoTypes.Contains(CargoType))
							{
								MutuallyBeneficialLocations.Add(Location);
								break;
							}
						}
					}
				}
				if(!MutuallyBeneficialLocations.IsEmpty())
				{
					InRequest.DestinationLocation = RandomEntryWithWeight(MutuallyBeneficialLocations, AlreadyUsedLocations);
				}
			}
			if(InRequest.DestinationLocation == nullptr)
			{
				InRequest.DestinationLocation = RandomEntryWithWeight(InDataMap->SubLocationWeights, AlreadyUsedLocations);
			}
		}
	}
}

void CustomsRequestsHelper::GenerateCargoManifest(FCustomsRequest& InRequest, const UCustomsRequestDataMap* InDataMap, const UDayDefinitionAsset* InDayDefinition)
{
	if(InRequest.CargoManifest.ShipName.IsEmpty())
	{
		const TMap<int32, float>& ShipNameComplexityListToUse = InRequest.Faction != nullptr && !InRequest.Faction->NameComplexityModifiers.IsEmpty() ?
			InRequest.Faction->NameComplexityModifiers : InDataMap->Names->ShipNameComplexityModifiers;
		const UDataTable* ShipNamePrefixTableToUse = InRequest.Faction != nullptr && InRequest.Faction->ShipNamePrefixes != nullptr ?
			InRequest.Faction->ShipNamePrefixes : InDataMap->Names->ShipNamePrefixes;
		const UDataTable* ShipNameTableToUse = InRequest.Faction != nullptr && InRequest.Faction->ShipNameWords != nullptr ?
			InRequest.Faction->ShipNameWords : InDataMap->Names->ShipNameWords;
		
		const int32 ShipNameComplexity = RandomEntryWithWeight<int32>(ShipNameComplexityListToUse);

		const TArray<FName>& PrefixNames = ShipNamePrefixTableToUse->GetRowNames();
		const TArray<FName>& ShipNameWords = ShipNameTableToUse->GetRowNames();
		
		const FNameDefinitionData* ChosenPrefix = ShipNamePrefixTableToUse->FindRow<FNameDefinitionData>(PrefixNames[FMath::RandRange(0, PrefixNames.Num() - 1)], CustomsRequestsHelperPrivates::CustomsRequestHelperDataTableContextString);
		InRequest.CargoManifest.ShipName.Append(ChosenPrefix->Name.ToString());
		for(int32 i = 0; i < ShipNameComplexity; i++)
		{
			if(!InRequest.CargoManifest.ShipName.IsEmpty())
			{
				InRequest.CargoManifest.ShipName.Append(TEXT(" "));
			}
			
			const FNameDefinitionData* ChosenWord = ShipNameTableToUse->FindRow<FNameDefinitionData>(ShipNameWords[FMath::RandRange(0, ShipNameWords.Num() - 1)], CustomsRequestsHelperPrivates::CustomsRequestHelperDataTableContextString);
			InRequest.CargoManifest.ShipName.Append(ChosenWord->Name.ToString());
		}
	}

	if(InRequest.OriginLocation != nullptr)
	{
		InRequest.CargoManifest.OriginSubLocation = InRequest.OriginLocation->Name;
		if(ULocationDefinition* LocationDefinition = InRequest.OriginLocation->Location)
		{
			InRequest.CargoManifest.OriginLocation = LocationDefinition->Name;
		}
	}

	if(InRequest.DestinationLocation != nullptr)
	{
		InRequest.CargoManifest.DestinationSubLocation = InRequest.DestinationLocation->Name;
		if(ULocationDefinition* LocationDefinition = InRequest.DestinationLocation->Location)
		{
			InRequest.CargoManifest.DestinationLocation = LocationDefinition->Name;
		}
	}

	TMap<UCargoTypeDefinition*, float> MutualCargoTypes;
	for(UCargoTypeDefinition* SuppliedCargoType : InRequest.OriginLocation->SuppliedCargoTypes)
	{
		if(InRequest.DestinationLocation->SuppliedCargoTypes.Contains(SuppliedCargoType))
		{
			MutualCargoTypes.Add(SuppliedCargoType, SuppliedCargoType->SelectionWeight + (SuppliedCargoType->Category != nullptr ? SuppliedCargoType->Category->SelectionWeight : 0.0f));
		}
	}

	const int32 CargoComplexity = RandomEntryWithWeight(InDayDefinition->CargoManifestComplexityWeights);
	
	float RemainingWeight = InRequest.Ship->MaximumWeight;
	int32 UnitsLeft = InRequest.Ship->UnitCapacity;

	TArray<UCargoTypeDefinition*> AlreadyUsedCargo;
	for(int32 i = 0; i < CargoComplexity; i++)
	{
		const int32 MinimumUnits = FMath::Min(FMath::FloorToInt32(static_cast<float>(InRequest.Ship->UnitCapacity) * (i / CargoComplexity)), UnitsLeft);
		if(MutualCargoTypes.Num() > 0 ? FMath::RandBool() : false)
		{
			if(UCargoTypeDefinition* ChosenCargoType = RandomEntryWithWeight(MutualCargoTypes, AlreadyUsedCargo); ChosenCargoType != nullptr)
			{
				if(int32 UnitsChosen = FMath::RandRange(MinimumUnits, FMath::Min(UnitsLeft, static_cast<int32>(FMath::Floor(RemainingWeight / (ChosenCargoType->WeightMultiplierPerUnit))))); UnitsChosen > 0)
				{
					InRequest.CargoManifest.Cargo.Emplace(ChosenCargoType, UnitsChosen);
					RemainingWeight -= UnitsChosen * ChosenCargoType->WeightMultiplierPerUnit;
					UnitsLeft -= UnitsChosen;
					AlreadyUsedCargo.Add(ChosenCargoType);
					continue;
				}
			}
		}
		
		if(UCargoTypeDefinition* ChosenCargoType = RandomEntryWithWeight(InDataMap->CargoWeights, AlreadyUsedCargo))
		{
			if(int32 UnitsChosen = FMath::RandRange(MinimumUnits, FMath::Min(UnitsLeft, static_cast<int32>(FMath::Floor(RemainingWeight / (ChosenCargoType->WeightMultiplierPerUnit))))); UnitsChosen > 0)
			{
				InRequest.CargoManifest.Cargo.Emplace(ChosenCargoType, UnitsChosen);
				RemainingWeight -= UnitsChosen * ChosenCargoType->WeightMultiplierPerUnit;
				UnitsLeft -= UnitsChosen;
				AlreadyUsedCargo.Add(ChosenCargoType);
				continue;
			}
		}
		
		break;
	}
}

void CustomsRequestsHelper::GenerateCargoFromParameters(FCargoManifest& InManifest,
	const TMap<ECustomsRequestModifier, float>& RequestModifiers, const USubLocationDefinition* Origin,
	const USubLocationDefinition* Destination)
{	
}

void CustomsRequestsHelper::FillFromCharacterAppearance(FCustomsRequest& InRequest)
{
	if(InRequest.CharacterAppearance != nullptr)
	{
		InRequest.CargoManifest.ShipName = InRequest.CharacterAppearance->Character->ShipName;
		InRequest.RequestType = InRequest.CharacterAppearance->CustomsRequestType;
		InRequest.Faction = InRequest.CharacterAppearance->Character->Faction;
		InRequest.Ship = InRequest.CharacterAppearance->Character->ShipClass;
		
		if(USubLocationDefinition* SubLocationDefinition = InRequest.CharacterAppearance->OriginLocation)
		{
			InRequest.OriginLocation = SubLocationDefinition;
			InRequest.CargoManifest.OriginSubLocation = SubLocationDefinition->Name;
			
			if(ULocationDefinition* LocationDefinition = SubLocationDefinition->Location)
			{
				InRequest.CargoManifest.OriginLocation = LocationDefinition->Name;
			}
		}
		
		if(USubLocationDefinition* SubLocationDefinition = InRequest.CharacterAppearance->DestinationLocation)
		{
			InRequest.DestinationLocation = SubLocationDefinition;
			InRequest.CargoManifest.DestinationSubLocation = SubLocationDefinition->Name;
			
			if(ULocationDefinition* LocationDefinition = SubLocationDefinition->Location)
			{
				InRequest.CargoManifest.DestinationLocation = LocationDefinition->Name;
			}
		}
		GenerateCargoFromParameters(InRequest.CargoManifest, InRequest.CharacterAppearance->CharacterModifiers, InRequest.CharacterAppearance->OriginLocation, InRequest.CharacterAppearance->DestinationLocation);
	}
}
