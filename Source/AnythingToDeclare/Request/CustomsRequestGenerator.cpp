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
	GenerateCargoManifest(InRequest, InDataMap, InDayDefinition);
}

void CustomsRequestsHelper::GenerateCharacter(FCustomsRequest& InRequest, const UCustomsRequestDataMap* InDataMap,
	const UGameplayTagContextAsset* InGameplayTagContexts, const UDayDefinitionAsset* InDayDefinition)
{
	if(InRequest.CharacterAppearance == nullptr && InRequest.Character.CurrentTags.IsEmpty())
	{
		TArray<TPair<FGameplayTag, float>> ShuffledCharacterModifiers = InDayDefinition->CharacterModifiers.Array();
		const int32 NumShuffles = ShuffledCharacterModifiers.Num() - 1;
		for(int32 i = 0 ; i < NumShuffles ; ++i)
		{
			const int32 SwapIdx = FMath::RandRange(i, NumShuffles);
			ShuffledCharacterModifiers.Swap(i, SwapIdx);
		}
		
		for(const TPair<FGameplayTag, float>& TagChance : ShuffledCharacterModifiers)
		{
			// TODO: Disallow if existing chosen tags prevent this one.
			if(FMath::Rand() >= TagChance.Value)
			{
				InRequest.Character.CurrentTags.Add(TagChance.Key);
			}
		}
	}
		
	if(InRequest.Character.Age == 0)
	{
		InRequest.Character.Age = FMath::RandRange(20, 70);
	}
	if(InRequest.Character.CryogenicAge == 0)
	{
		if(InRequest.Character.CurrentTags.Contains(InGameplayTagContexts->CryogenicTag))
		{
			InRequest.Character.CryogenicAge = FMath::Min(InRequest.Character.Age + FMath::RandRange(1, 125), 125);
		}
		else
		{
			InRequest.Character.CryogenicAge = InRequest.Character.Age;
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

void CustomsRequestsHelper::GenerateCargoManifest(FCustomsRequest& InRequest, const UCustomsRequestDataMap* InDataMap, const UDayDefinitionAsset* InDayDefinition)
{
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

		TArray<TPair<FGameplayTag, float>> ShuffledCharacterModifiers = InRequest.CharacterAppearance->CharacterModifiers.Array();
		const int32 NumShuffles = ShuffledCharacterModifiers.Num() - 1;
		for(int32 i = 0 ; i < NumShuffles ; ++i)
		{
			const int32 SwapIdx = FMath::RandRange(i, NumShuffles);
			ShuffledCharacterModifiers.Swap(i, SwapIdx);
		}
		
		for(const TPair<FGameplayTag, float>& TagChance : ShuffledCharacterModifiers)
		{
			// TODO: Disallow if existing chosen tags prevent this one.
			if(FMath::Rand() >= TagChance.Value)
			{
				InRequest.Character.CurrentTags.Add(TagChance.Key);
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
