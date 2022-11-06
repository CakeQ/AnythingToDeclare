// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#include "CustomsRequestGenerator.h"

#include "CustomsRequestDataMap.h"
#include "AnythingToDeclare/Character/CharacterDefinitionAsset.h"
#include "AnythingToDeclare/Day/DayDefinition.h"
#include "AnythingToDeclare/Fluff/Location/LocationDefinition.h"
#include "AnythingToDeclare/Fluff/Location/SubLocationDefinition.h"
#include "AnythingToDeclare/Fluff/Names/NameDefinitionMap.h"

void CustomsRequestsHelper::GenerateRequest(FCustomsRequest& InRequest, const UCustomsRequestDataMap* InDataMap, const UDayDefinitionAsset* InDayDefinition)
{
	FillFromCharacterAppearance(InRequest);
	GenerateCargoRoute(InRequest, InDataMap, InDayDefinition);
	GenerateCargoManifest(InRequest.CargoManifest, InDataMap, InDayDefinition, InRequest.OriginLocation, InRequest.DestinationLocation);
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

void CustomsRequestsHelper::GenerateCargoManifest(FCargoManifest& InManifest, const UCustomsRequestDataMap* InDataMap,
                                                  const UDayDefinitionAsset* InDayDefinition, const USubLocationDefinition* Origin, const USubLocationDefinition* Destination)
{
	if(InManifest.ShipName.IsEmpty())
	{
		const int32 ShipNameComplexity = RandomEntryWithWeight<int32>(InDataMap->Names->ShipNameComplexityModifiers);
		
		const int32 PrefixIndex = FMath::RandRange(0, InDataMap->Names->ShipNamePrefixes.Num() - 1);
		InManifest.ShipName.Append(InDataMap->Names->ShipNamePrefixes[PrefixIndex]);
		for(int32 i = 0; i < ShipNameComplexity; i++)
		{
			if(!InManifest.ShipName.IsEmpty())
			{
				InManifest.ShipName.Append(TEXT(" "));
			}
			const int32 NameIndex = FMath::RandRange(0, InDataMap->Names->ShipNameWords.Num() - 1);
			InManifest.ShipName.Append(InDataMap->Names->ShipNameWords[NameIndex]);
		}
	}

	if(Origin != nullptr)
	{
		InManifest.OriginSubLocation = Origin->Name;
		if(ULocationDefinition* LocationDefinition = Origin->Location)
		{
			InManifest.OriginLocation = LocationDefinition->Name;
		}
	}

	if(Destination != nullptr)
	{
		InManifest.DestinationSubLocation = Destination->Name;
		if(ULocationDefinition* LocationDefinition = Destination->Location)
		{
			InManifest.DestinationLocation = LocationDefinition->Name;
		}
	}

	TArray<UCargoTypeDefinition*> MutualCargoTypes;

	for(UCargoTypeDefinition* DemandedCargoType : Origin->DemandedCargoTypes)
	{
		if(Destination->SuppliedCargoTypes.Contains(DemandedCargoType))
		{
			MutualCargoTypes.AddUnique(DemandedCargoType);
		}
	}
	for(UCargoTypeDefinition* SuppliedCargoType : Origin->SuppliedCargoTypes)
	{
		if(Destination->SuppliedCargoTypes.Contains(SuppliedCargoType))
		{
			MutualCargoTypes.AddUnique(SuppliedCargoType);
		}
	}

	const int32 CargoComplexity = RandomEntryWithWeight(InDayDefinition->CargoManifestComplexityWeights);
	
	// TODO: Remove magic number
	float RemainingWeight = 1000.0f;
	int32 UnitsLeft = 100;

	for(int32 i = 0; i < CargoComplexity; i++)
	{
		if(MutualCargoTypes.Num() > 0 ? FMath::RandBool() : false)
		{
			const int32 PickedIndex = FMath::RandRange(0, MutualCargoTypes.Num() - 1);
			UCargoTypeDefinition* ChosenCargoType = MutualCargoTypes[PickedIndex];
			if(int32 UnitsChosen = FMath::RandRange(1, FMath::Min(UnitsLeft, static_cast<int32>(FMath::Floor(RemainingWeight / (ChosenCargoType->WeightMultiplierPerUnit))))); UnitsChosen > 0)
			{
				InManifest.Cargo.Emplace(ChosenCargoType, UnitsChosen);
				RemainingWeight -= UnitsChosen * ChosenCargoType->WeightMultiplierPerUnit;
				UnitsLeft -= UnitsChosen;
				continue;
			}
		}
		
		const int32 PickedIndex = FMath::RandRange(0, InDataMap->CargoTypes.Num() - 1);
		UCargoTypeDefinition* ChosenCargoType = InDataMap->CargoTypes[PickedIndex];
		if(int32 UnitsChosen = FMath::RandRange(1, FMath::Min(UnitsLeft, static_cast<int32>(FMath::Floor(RemainingWeight / (ChosenCargoType->WeightMultiplierPerUnit))))); UnitsChosen > 0)
		{
			InManifest.Cargo.Emplace(ChosenCargoType, UnitsChosen);
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
