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
#include "AnythingToDeclare/Settings/GameplayTagContextAsset.h"
#include "AnythingToDeclare/Settings/RequestTagContext.h"
#include "Logging/LogMacros.h"

DEFINE_LOG_CATEGORY_STATIC(CustomsRequestsHelperLog, Log, All)

namespace
{
	namespace CustomsRequestsHelperPrivates
	{
		const FString CustomsRequestHelperDataTableContextString = TEXT("CustomsRequestsHelper");
	}
}

void CustomsRequestsHelper::GenerateRequest(FCustomsRequest& InRequest, const UCustomsRequestDataMap* InDataMap,
	const UGameplayTagContextAsset* InGameplayTagContexts, const UDayDefinitionAsset* InDayDefinition)
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
	GenerateCharacter(InRequest, InDataMap, InGameplayTagContexts, InDayDefinition);
	GenerateCargoRoute(InRequest, InDataMap, InDayDefinition);
	GenerateCargoManifest(InRequest, InDataMap, InGameplayTagContexts, InDayDefinition);
}

void CustomsRequestsHelper::GenerateCharacter(FCustomsRequest& InRequest, const UCustomsRequestDataMap* InDataMap,
	const UGameplayTagContextAsset* InGameplayTagContexts, const UDayDefinitionAsset* InDayDefinition)
{
	if(InRequest.CharacterAppearance == nullptr)
	{
		if(InRequest.RequestTags.IsEmpty())
		{
			const int32 RequestModifiersComplexity = RandomEntryWithWeight(InDayDefinition->RequestModifierComplexityWeights);
			TArray<FGameplayTag> AlreadyAddedTags;
			for(int32 i = 0 ; i < RequestModifiersComplexity ; ++i)
			{
				if(FGameplayTag TagToAdd = RandomEntryWithWeight(InDayDefinition->RequestModifierWeights, AlreadyAddedTags); TagToAdd.IsValid())
				{
					AlreadyAddedTags.Add(TagToAdd);
					InRequest.RequestTags.Add(TagToAdd);
				}
			}
		}
	}

	if(InRequest.Character.Age == 0)
	{
		InRequest.Character.Age = FMath::RandRange(20, 70);
	}
	if(InRequest.Character.CryogenicAge == 0)
	{
		InRequest.Character.CryogenicAge = InRequest.Character.Age;
		for(const FGameplayTag& Tag : InRequest.RequestTags)
		{
			if(InGameplayTagContexts->RequestModifiers.FindByPredicate([Tag](const FGameplayTagContextData& Iterator){ return Iterator.Tag.MatchesTag(Tag) && Iterator.Context == EGameplayTagContext::IDAgeCryo;}))
			{
				InRequest.Character.CryogenicAge = FMath::Min(InRequest.Character.Age + FMath::RandRange(1, 125), 125);
				break;
			}
		}
	}

	if(InRequest.Character.Portrait == nullptr)
	{
		// TODO
		// InRequest.Character.Portrait = GeneratePortrait();
	}
	
	if(InRequest.Character.FacePortrait == nullptr)
	{
		// TODO
		// InRequest.Character.FacePortrait = GenerateFacePortrait();
	}
	
	if(InRequest.Character.Names.IsEmpty())
	{
		TMap<int32, float>& NameComplexityToUse = InDataMap->Names->NameComplexityModifiers;
		const UDataTable* NameTableToUse = InDataMap->Names->Names;

		int32 CurrentPriority = InDataMap->Names->NamePriority;
		if(InRequest.Faction != nullptr && InRequest.Faction->FactionNameOverrides != nullptr)
		{
			if(InRequest.Faction->FactionNameOverrides->CallSignPriority > CurrentPriority)
			{
				NameComplexityToUse = InRequest.Faction->FactionNameOverrides->NameComplexityModifiers;
				NameTableToUse = InRequest.Faction->FactionNameOverrides->Names;
				CurrentPriority = InRequest.Faction->FactionNameOverrides->NamePriority;
			}
			else if(InRequest.Faction->FactionNameOverrides->NamePriority == CurrentPriority)
			{
				if(FMath::RandBool())
				{
					NameComplexityToUse = InRequest.Faction->FactionNameOverrides->NameComplexityModifiers;
					NameTableToUse = InRequest.Faction->FactionNameOverrides->Names;
				}
			}
		}
		
		const int32 NameComplexity = RandomEntryWithWeight(NameComplexityToUse);
		const TArray<FName>& Names = NameTableToUse->GetRowNames();
		for(int32 i = 0; i < NameComplexity; i++)
		{
			const FNameDefinitionData* ChosenName = NameTableToUse->FindRow<FNameDefinitionData>(Names[FMath::RandRange(0, Names.Num() - 1)], CustomsRequestsHelperPrivates::CustomsRequestHelperDataTableContextString);
			if(ChosenName != nullptr)
			{
				InRequest.Character.Names.Add(ChosenName->Name.ToString());
			}
		}
	}
	
	if(InRequest.Character.Surname.IsEmpty())
	{
		TMap<int32, float>& SurnameComplexityToUse = InDataMap->Names->SurnameComplexityModifiers;
		const UDataTable* SurnameTableToUse = InDataMap->Names->Surnames;

		int32 CurrentPriority = InDataMap->Names->SurnamePriority;
		if(InRequest.Faction != nullptr && InRequest.Faction->FactionNameOverrides != nullptr)
		{
			if(InRequest.Faction->FactionNameOverrides->CallSignPriority > CurrentPriority)
			{
				SurnameComplexityToUse = InRequest.Faction->FactionNameOverrides->SurnameComplexityModifiers;
				SurnameTableToUse = InRequest.Faction->FactionNameOverrides->Surnames;
				CurrentPriority = InRequest.Faction->FactionNameOverrides->SurnamePriority;
			}
			else if(InRequest.Faction->FactionNameOverrides->SurnamePriority == CurrentPriority)
			{
				if(FMath::RandBool())
				{
					SurnameComplexityToUse = InRequest.Faction->FactionNameOverrides->SurnameComplexityModifiers;
					SurnameTableToUse = InRequest.Faction->FactionNameOverrides->Surnames;
				}
			}
		}
		
		const int32 SurnameComplexity = RandomEntryWithWeight(SurnameComplexityToUse);
		const TArray<FName>& Surnames = SurnameTableToUse->GetRowNames();
		for(int32 i = 0; i < SurnameComplexity; i++)
		{
			const FNameDefinitionData* ChosenName = SurnameTableToUse->FindRow<FNameDefinitionData>(Surnames[FMath::RandRange(0, Surnames.Num() - 1)], CustomsRequestsHelperPrivates::CustomsRequestHelperDataTableContextString);
			if(i != 0)
			{
				InRequest.Character.Surname.Append(FString::Printf(TEXT("-%s"), *ChosenName->Name.ToString()));
			}
			else
			{
				InRequest.Character.Surname = ChosenName->Name.ToString();
			}
		}
	}

	if(InRequest.Character.CallSign.IsEmpty())
	{
		const UNameDefinitionMap* CallSignsToUse = InDataMap->Names;
		int32 CurrentPriority = CallSignsToUse->CallSignPriority;
		if(InRequest.Faction != nullptr && InRequest.Faction->FactionNameOverrides != nullptr)
		{
			if(InRequest.Faction->FactionNameOverrides->CallSignPriority > CurrentPriority)
			{
				CallSignsToUse = InRequest.Faction->FactionNameOverrides;
				CurrentPriority = InRequest.Faction->FactionNameOverrides->CallSignPriority;
			}
			else if(InRequest.Faction->FactionNameOverrides->CallSignPriority == CurrentPriority)
			{
				if(FMath::RandBool())
				{
					CallSignsToUse = InRequest.Faction->FactionNameOverrides;
				}
			}
		}
		
		const int32 CallSignComplexity = RandomEntryWithWeight(CallSignsToUse->CallSignComplexityModifiers);
		for(int32 i = 0; i < CallSignComplexity; i++)
		{
			FString ChosenWord;
			if(i == 0 && CallSignComplexity > 1 && !CallSignsToUse->CallSignAdjectives.IsEmpty() && FMath::RandBool())
			{
				ChosenWord = CallSignsToUse->CallSignAdjectives[FMath::RandRange(0, CallSignsToUse->CallSignAdjectives.Num() - 1)].ToString();
			}
			else
			{
				ChosenWord = CallSignsToUse->CallSignNouns[FMath::RandRange(0, CallSignsToUse->CallSignNouns.Num() - 1)].ToString();
			}

			if(ChosenWord.Contains(TEXT("{name}")))
			{
				ChosenWord = ChosenWord.Replace(TEXT("{name}"), *InRequest.Character.Names[FMath::RandRange(0, InRequest.Character.Names.Num() - 1)]);
			}
			if(ChosenWord.Contains(TEXT("{surname}")))
			{
				ChosenWord = ChosenWord.Replace(TEXT("{surname}"), *InRequest.Character.Surname);
			}
			// TODO: Integrate year of birth codename
			// if(ChosenWord.Contains(TEXT("{yearofbirth}")))
			// {
			// 	ChosenWord = ChosenWord.Replace(TEXT("{yearofbirth}"), *InRequest.Character.Age);
			// }
			
			InRequest.Character.CallSign.Append(ChosenWord);
		}
	}

	if(InRequest.Character.ShipName.IsEmpty())
	{
		const UNameDefinitionMap* ShipNamesToUse = InDataMap->Names;
		int32 CurrentPriority = InDataMap->Names->ShipNamePriority;
		if(InRequest.Faction != nullptr && InRequest.Faction->FactionNameOverrides != nullptr)
		{
			if(InRequest.Faction->FactionNameOverrides->ShipNamePriority > CurrentPriority)
			{
				ShipNamesToUse = InRequest.Faction->FactionNameOverrides;
				CurrentPriority = InRequest.Faction->FactionNameOverrides->ShipNamePriority;
			}
			else if(InRequest.Faction->FactionNameOverrides->ShipNamePriority == CurrentPriority)
			{
				if(FMath::RandBool())
				{
					ShipNamesToUse = InRequest.Faction->FactionNameOverrides;
				}
			}
		}
		
		const int32 ShipNameComplexity = RandomEntryWithWeight<int32>(ShipNamesToUse->ShipNameComplexityModifiers);
		const TArray<FName>& PrefixNames = ShipNamesToUse->ShipNamePrefixes->GetRowNames();

		const FNameDefinitionData* ChosenPrefix = ShipNamesToUse->ShipNamePrefixes->FindRow<FNameDefinitionData>(PrefixNames[FMath::RandRange(0, PrefixNames.Num() - 1)], CustomsRequestsHelperPrivates::CustomsRequestHelperDataTableContextString);
		InRequest.Character.ShipName.Append(ChosenPrefix->Name.ToString());
		for(int32 i = 0; i < ShipNameComplexity; i++)
		{
			if(!InRequest.Character.ShipName.IsEmpty())
			{
				InRequest.Character.ShipName.Append(TEXT(" "));
			}

			FString ChosenWord;
			if(i == 0 && ShipNameComplexity > 1 && !ShipNamesToUse->ShipNameAdjectives.IsEmpty() && FMath::RandBool())
			{
				ChosenWord = ShipNamesToUse->ShipNameAdjectives[FMath::RandRange(0, ShipNamesToUse->ShipNameAdjectives.Num() - 1)].ToString();
			}
			else
			{
				ChosenWord = ShipNamesToUse->ShipNameNouns[FMath::RandRange(0, ShipNamesToUse->ShipNameNouns.Num() - 1)].ToString();
			}
			
			InRequest.Character.ShipName.Append(ChosenWord);
		}
	}
}

void CustomsRequestsHelper::GenerateCargoRoute(FCustomsRequest& InRequest, const UCustomsRequestDataMap* InDataMap,
                                               const UDayDefinitionAsset* InDayDefinition)
{
	USubLocationDefinition* WorkLocation = InDayDefinition->WorkLocationOverride != nullptr ? InDayDefinition->WorkLocationOverride : InDataMap->DefaultWorkLocation;
	if(InRequest.RequestType == ECustomsRequestType::None)
	{
		InRequest.RequestType = RandomEntryWithWeight(InDayDefinition->CustomsRequestTypeWeight);
	}

	TArray<USubLocationDefinition*> AlreadyUsedLocations;
	if(InRequest.OriginLocation == nullptr)
	{
		if(InRequest.RequestType == ECustomsRequestType::Outbound)
		{
			InRequest.OriginLocation = WorkLocation;
		}
		else
		{
			AlreadyUsedLocations.Add(WorkLocation);
			InRequest.OriginLocation = RandomEntryWithWeight(InDataMap->SubLocationWeights, AlreadyUsedLocations);
		}
		AlreadyUsedLocations.Add(InRequest.OriginLocation);
		if(InRequest.RequestType == ECustomsRequestType::Transfer)
		{
			AlreadyUsedLocations.Append(InDataMap->SubLocations.FilterByPredicate([OriginLocation = InRequest.OriginLocation](const USubLocationDefinition* Iterator){ return OriginLocation-> Location != nullptr && Iterator->Location == OriginLocation->Location;}));
		}
	}

	if(InRequest.DestinationLocation == nullptr)
	{
		if(InRequest.RequestType == ECustomsRequestType::Inbound)
		{
			InRequest.DestinationLocation = WorkLocation;
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

void CustomsRequestsHelper::GenerateCargoManifest(FCustomsRequest& InRequest, const UCustomsRequestDataMap* InDataMap, const UGameplayTagContextAsset* InGameplayTagContexts, const UDayDefinitionAsset* InDayDefinition)
{
	TArray<const FGameplayTagContextData*> CargoContexts;
	TArray<EGameplayTagContext> TypoFields;
	if(InGameplayTagContexts != nullptr)
	{
		for(const FGameplayTag& RequestTag : InRequest.RequestTags)
		{
			if(const FGameplayTagContextData* TagContext = InGameplayTagContexts->FindRequestTagContextData(RequestTag))
			{
				if(TagContext->Context == EGameplayTagContext::ManifestCargo)
				{
					CargoContexts.Add(TagContext);
				}
			}
			else if(TagContext->Modifiers.Contains(EGameplayTagModifier::HasTypo))
			{
				TypoFields.Add(TagContext->Context);
			}
		}
	}
	
	if(InRequest.CargoManifest.ShipName.IsEmpty())
	{
		InRequest.CargoManifest.ShipName = InRequest.Character.ShipName;
	}

	if(InRequest.OriginLocation != nullptr)
	{
		InRequest.CargoManifest.OriginSubLocation = InRequest.OriginLocation->Name;
		if(ULocationDefinition* LocationDefinition = InRequest.OriginLocation->Location)
		{
			InRequest.CargoManifest.OriginLocation = LocationDefinition->Name;
		}
		if(TypoFields.Contains(EGameplayTagContext::ManifestOrigin))
		{
			if(FMath::RandBool())
			{
				if(InRequest.OriginLocation->NameTypos.IsEmpty())
				{
					UE_LOG(CustomsRequestsHelperLog, Error, TEXT("CustomsRequestsHelper::GenerateCargoManifest - sublocation definition %s missing typos"), *InRequest.OriginLocation->Name);
				}
				else
				{
					InRequest.CargoManifest.OriginSubLocation = InRequest.OriginLocation->NameTypos[FMath::RandRange(0, InRequest.OriginLocation->NameTypos.Num() - 1)];
				}
			}
			else if(ULocationDefinition* LocationDefinition = InRequest.OriginLocation->Location)
			{
				if(LocationDefinition->NameTypos.IsEmpty())
				{
					UE_LOG(CustomsRequestsHelperLog, Error, TEXT("CustomsRequestsHelper::GenerateCargoManifest - location definition %s missing typos"), *LocationDefinition->Name);
				}
				else
				{
					InRequest.CargoManifest.OriginLocation = LocationDefinition->NameTypos[FMath::RandRange(0, LocationDefinition->NameTypos.Num() - 1)];
				}
			}
		}
	}

	if(InRequest.DestinationLocation != nullptr)
	{
		InRequest.CargoManifest.DestinationSubLocation = InRequest.DestinationLocation->Name;
		if(ULocationDefinition* LocationDefinition = InRequest.DestinationLocation->Location)
		{
			InRequest.CargoManifest.DestinationLocation = LocationDefinition->Name;
		}
		if(TypoFields.Contains(EGameplayTagContext::ManifestDestination))
		{
			if(FMath::RandBool())
			{
				if(InRequest.DestinationLocation->NameTypos.IsEmpty())
				{
					UE_LOG(CustomsRequestsHelperLog, Error, TEXT("CustomsRequestsHelper::GenerateCargoManifest - sublocation definition %s missing typos"), *InRequest.DestinationLocation->Name);
				}
				else
				{
					InRequest.CargoManifest.DestinationSubLocation = InRequest.DestinationLocation->NameTypos[FMath::RandRange(0, InRequest.DestinationLocation->NameTypos.Num() - 1)];
				}
			}
			else if(ULocationDefinition* LocationDefinition = InRequest.DestinationLocation->Location)
			{
				if(LocationDefinition->NameTypos.IsEmpty())
				{
					UE_LOG(CustomsRequestsHelperLog, Error, TEXT("CustomsRequestsHelper::GenerateCargoManifest - location definition %s missing typos"), *LocationDefinition->Name);
				}
				else
				{
					InRequest.CargoManifest.DestinationLocation = LocationDefinition->NameTypos[FMath::RandRange(0, LocationDefinition->NameTypos.Num() - 1)];
				}
			}
		}
	}

	TMap<UCargoTypeDefinition*, float> MutualCargoTypes;
	TMap<UCargoTypeDefinition*, float> MutualContraband;
	if(InRequest.OriginLocation != nullptr && InRequest.DestinationLocation != nullptr)
	{
		for(UCargoTypeDefinition* SuppliedCargoType : InRequest.OriginLocation->SuppliedCargoTypes)
		{
			if(InRequest.DestinationLocation->SuppliedCargoTypes.Contains(SuppliedCargoType))
			{
				if(SuppliedCargoType->IsIllegal)
				{
					MutualContraband.Add(SuppliedCargoType, SuppliedCargoType->SelectionWeight + (SuppliedCargoType->Category != nullptr ? SuppliedCargoType->Category->SelectionWeight : 0.0f));
				}
				else
				{
					MutualCargoTypes.Add(SuppliedCargoType, SuppliedCargoType->SelectionWeight + (SuppliedCargoType->Category != nullptr ? SuppliedCargoType->Category->SelectionWeight : 0.0f));
				}
			}
		}
	}
	
	const int32 CargoComplexity = RandomEntryWithWeight(InDayDefinition->CargoManifestComplexityWeights);
	
	float RemainingWeight = InRequest.Ship->MaximumWeight;
	int32 UnitsLeft = InRequest.Ship->UnitCapacity;

	TArray<UCargoTypeDefinition*> AlreadyUsedCargo;
	TArray<const FGameplayTagContextData*> UnfulfilledCargoContexts;

	for(int32 i = 0; i < CargoComplexity; i++)
	{
		const TMap<UCargoTypeDefinition*, float>* MutualCargoTypesToUse = &MutualCargoTypes;
		const TMap<UCargoTypeDefinition*, float>* StandardCargoTypesToUse = &InDataMap->CargoWeights;
		
		FCargoManifestEntry NewEntry;
		
		if(CargoContexts.Num() > i)
		{
			if(const FGameplayTagContextData* TagContext = CargoContexts[i])
			{
				if(TagContext->Modifiers.Contains(EGameplayTagModifier::Illegal))
				{
					MutualCargoTypesToUse = &MutualContraband;
					StandardCargoTypesToUse = &InDataMap->ContrabandWeights;
				}
				NewEntry.Modifiers = TagContext->Modifiers;
			}
		}

		const int32 MinimumUnits = FMath::Min(FMath::FloorToInt32(static_cast<float>(InRequest.Ship->UnitCapacity) * (i / CargoComplexity)), UnitsLeft);
		if(MutualCargoTypes.Num() > 0 ? FMath::RandBool() : false)
		{
			if(UCargoTypeDefinition* ChosenCargoType = RandomEntryWithWeight(*MutualCargoTypesToUse, AlreadyUsedCargo); ChosenCargoType != nullptr)
			{
				if(const int32 UnitsChosen = FMath::RandRange(MinimumUnits, FMath::Min(UnitsLeft, static_cast<int32>(FMath::Floor(RemainingWeight / (ChosenCargoType->WeightMultiplierPerUnit))))); UnitsChosen > 0)
				{
					NewEntry.CargoType = ChosenCargoType;
					NewEntry.DisplayedCargoType = ChosenCargoType;
					NewEntry.TotalUnits = UnitsChosen;
				}
			}
		}
		
		if(UCargoTypeDefinition* ChosenCargoType = RandomEntryWithWeight(*StandardCargoTypesToUse, AlreadyUsedCargo))
		{
			if(const int32 UnitsChosen = FMath::RandRange(MinimumUnits, FMath::Min(UnitsLeft, static_cast<int32>(FMath::Floor(RemainingWeight / (ChosenCargoType->WeightMultiplierPerUnit))))); UnitsChosen > 0)
			{
				NewEntry.CargoType = ChosenCargoType;
				NewEntry.DisplayedCargoType = ChosenCargoType;
				NewEntry.TotalUnits = UnitsChosen;
			}
		}

		if(NewEntry.CargoType != nullptr)
		{
			NewEntry.DisplayWeightMultiplierPerUnit = NewEntry.CargoType->WeightMultiplierPerUnit;
			RemainingWeight -= NewEntry.TotalUnits * NewEntry.CargoType->WeightMultiplierPerUnit;
			UnitsLeft -= NewEntry.TotalUnits;
			AlreadyUsedCargo.Add(NewEntry.CargoType);

			if(const bool CompletelyFakeEntry =  NewEntry.Modifiers.Contains(EGameplayTagModifier::Fake); CompletelyFakeEntry || NewEntry.Modifiers.Contains(EGameplayTagModifier::NameSwapped))
			{
				UCargoTypeDefinition* ChosenCargoType = nullptr;
				if(MutualCargoTypes.Num() > 0 ? FMath::RandBool() : false)
				{
					ChosenCargoType = RandomEntryWithWeight(MutualCargoTypes, AlreadyUsedCargo);
				}
				if(ChosenCargoType == nullptr)
				{
					ChosenCargoType = RandomEntryWithWeight(InDataMap->CargoWeights, AlreadyUsedCargo);
				}
				if(ChosenCargoType != nullptr)
				{
					NewEntry.DisplayedCargoType = ChosenCargoType;
					if(NewEntry.Modifiers.Contains(EGameplayTagModifier::HasTypo))
					{
						if(ChosenCargoType->NameTypos.IsEmpty())
						{
							UE_LOG(CustomsRequestsHelperLog, Error, TEXT("CustomsRequestsHelper::GenerateCargoManifest - cargo definition %s missing typos"), *ChosenCargoType->Name);
						}
						else
						{
							NewEntry.DisplayName = ChosenCargoType->NameTypos[FMath::RandRange(0, NewEntry.CargoType->NameTypos.Num() - 1)];
						}
					}
					else
					{
						NewEntry.DisplayName = ChosenCargoType->Name;
					}
					if(CompletelyFakeEntry)
					{
						NewEntry.DisplayWeightMultiplierPerUnit = ChosenCargoType->WeightMultiplierPerUnit;
					}
					AlreadyUsedCargo.Add(ChosenCargoType);
				}
			}
			else if(NewEntry.Modifiers.Contains(EGameplayTagModifier::HasTypo))
			{
				if(NewEntry.CargoType->NameTypos.IsEmpty())
				{
					UE_LOG(CustomsRequestsHelperLog, Error, TEXT("CustomsRequestsHelper::GenerateCargoManifest - cargo definition %s missing typos"), *NewEntry.CargoType->Name);
				}
				else
				{
					NewEntry.DisplayName = NewEntry.CargoType->NameTypos[FMath::RandRange(0, NewEntry.CargoType->NameTypos.Num() - 1)];
				}
			}
			if(NewEntry.DisplayName.IsEmpty())
			{
				NewEntry.DisplayName = NewEntry.CargoType->Name;
			}
			
			InRequest.CargoManifest.Cargo.Add(NewEntry);
			continue;
		}
		if(CargoContexts.Num() > i)
		{
			UnfulfilledCargoContexts.Add(CargoContexts[i]);
		}
		
		break;
	}
	
	for(const FGameplayTagContextData* UnfulfilledContext : UnfulfilledCargoContexts)
	{
		InRequest.RequestTags.Remove(UnfulfilledContext->Tag);
	}
}

void CustomsRequestsHelper::FillFromCharacterAppearance(FCustomsRequest& InRequest)
{
	if(InRequest.CharacterAppearance != nullptr)
	{
		InRequest.CargoManifest.ShipName = InRequest.CharacterAppearance->Character->ShipName;
		InRequest.RequestType = InRequest.CharacterAppearance->CustomsRequestType;
		InRequest.Faction = InRequest.CharacterAppearance->Character->Faction;
		InRequest.Ship = InRequest.CharacterAppearance->Character->ShipClass;

		InRequest.Character.Age = InRequest.CharacterAppearance->Character->Age;
		InRequest.Character.Names = InRequest.CharacterAppearance->Character->Names;
		InRequest.Character.Portrait = InRequest.CharacterAppearance->Character->Portrait;
		InRequest.Character.Surname = InRequest.CharacterAppearance->Character->Surname;
		InRequest.Character.CallSign = InRequest.CharacterAppearance->Character->CallSign;
		InRequest.Character.CryogenicAge = InRequest.CharacterAppearance->Character->CryogenicAge;
		InRequest.Character.FacePortrait = InRequest.CharacterAppearance->Character->FacePortrait;
		InRequest.Character.ShipName = InRequest.CharacterAppearance->Character->ShipName;

		TArray<TPair<FGameplayTag, float>> ShuffledRequestModifiers = InRequest.CharacterAppearance->RequestModifiers.Array();
		const int32 NumReqShuffles = ShuffledRequestModifiers.Num() - 1;
		for(int32 i = 0 ; i < NumReqShuffles ; ++i)
		{
			const int32 SwapIdx = FMath::RandRange(i, NumReqShuffles);
			ShuffledRequestModifiers.Swap(i, SwapIdx);
		}
		
		for(const TPair<FGameplayTag, float>& TagChance : ShuffledRequestModifiers)
		{
			if(FMath::RandRange(0.0f, 1.0f) < TagChance.Value)
			{
				InRequest.RequestTags.Add(TagChance.Key);
			}
		}
		
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
	}
}
