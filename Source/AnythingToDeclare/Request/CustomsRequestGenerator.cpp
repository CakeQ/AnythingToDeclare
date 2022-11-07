// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#include "CustomsRequestGenerator.h"

#include "CustomsRequestDataMap.h"
#include "AnythingToDeclare/Character/CharacterDefinitionAsset.h"
#include "AnythingToDeclare/Day/DayDefinition.h"
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

	if(InRequest.OriginLocation == nullptr)
	{
		switch(InRequest.RequestType)
		{
		case ECustomsRequestType::Outbound:
			InRequest.OriginLocation = InDayDefinition->WorkLocationOverride != nullptr ? InDayDefinition->WorkLocationOverride : InDataMap->DefaultWorkLocation;
			break;
		case ECustomsRequestType::Inbound:
			// TODO: Add more complex way of potentially picking an origin that supplies destination demanded cargo if inbound
			InRequest.OriginLocation = RandomEntryWithWeight(InDataMap->SubLocationWeights);
			break;
		default:
			InRequest.OriginLocation = RandomEntryWithWeight(InDataMap->SubLocationWeights);
			break;
		}
	}

	// TODO: Dont allow same as origin
	if(InRequest.DestinationLocation == nullptr)
	{
		if(InRequest.RequestType == ECustomsRequestType::Inbound)
		{
			InRequest.DestinationLocation = InDayDefinition->WorkLocationOverride != nullptr ? InDayDefinition->WorkLocationOverride : InDataMap->DefaultWorkLocation;
		}
		else
		{
			// TODO: Add more complex way of potentially picking a destination that demands origin supplied cargo
			InRequest.DestinationLocation = RandomEntryWithWeight(InDataMap->SubLocationWeights);
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

	TArray<UCargoTypeDefinition*> MutualCargoTypes;

	for(UCargoTypeDefinition* DemandedCargoType : InRequest.OriginLocation->DemandedCargoTypes)
	{
		if(InRequest.DestinationLocation->SuppliedCargoTypes.Contains(DemandedCargoType))
		{
			MutualCargoTypes.AddUnique(DemandedCargoType);
		}
	}
	for(UCargoTypeDefinition* SuppliedCargoType : InRequest.OriginLocation->SuppliedCargoTypes)
	{
		if(InRequest.DestinationLocation->SuppliedCargoTypes.Contains(SuppliedCargoType))
		{
			MutualCargoTypes.AddUnique(SuppliedCargoType);
		}
	}

	const int32 CargoComplexity = RandomEntryWithWeight(InDayDefinition->CargoManifestComplexityWeights);
	
	// TODO: Remove magic number
	float RemainingWeight = 1000.0f;
	int32 UnitsLeft = 100;

	// TODO: Prevent duplicate cargo types
	// TODO: Match CargoComplexity better
	for(int32 i = 0; i < CargoComplexity; i++)
	{
		if(MutualCargoTypes.Num() > 0 ? FMath::RandBool() : false)
		{
			const int32 PickedIndex = FMath::RandRange(0, MutualCargoTypes.Num() - 1);
			UCargoTypeDefinition* ChosenCargoType = MutualCargoTypes[PickedIndex];
			if(int32 UnitsChosen = FMath::RandRange(1, FMath::Min(UnitsLeft, static_cast<int32>(FMath::Floor(RemainingWeight / (ChosenCargoType->WeightMultiplierPerUnit))))); UnitsChosen > 0)
			{
				InRequest.CargoManifest.Cargo.Emplace(ChosenCargoType, UnitsChosen);
				RemainingWeight -= UnitsChosen * ChosenCargoType->WeightMultiplierPerUnit;
				UnitsLeft -= UnitsChosen;
				continue;
			}
		}
		
		const int32 PickedIndex = FMath::RandRange(0, InDataMap->CargoTypes.Num() - 1);
		UCargoTypeDefinition* ChosenCargoType = InDataMap->CargoTypes[PickedIndex];
		if(int32 UnitsChosen = FMath::RandRange(1, FMath::Min(UnitsLeft, static_cast<int32>(FMath::Floor(RemainingWeight / (ChosenCargoType->WeightMultiplierPerUnit))))); UnitsChosen > 0)
		{
			InRequest.CargoManifest.Cargo.Emplace(ChosenCargoType, UnitsChosen);
			RemainingWeight -= UnitsChosen * ChosenCargoType->WeightMultiplierPerUnit;
			UnitsLeft -= UnitsChosen;
			continue;
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
