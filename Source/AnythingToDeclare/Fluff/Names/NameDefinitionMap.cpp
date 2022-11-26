// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#include "NameDefinitionMap.h"

namespace
{
	namespace NameDefinitionMapPrivates
	{
		const FString RegenerateDataListsContextString(TEXT("UNameDefinitionMap::RegenerateDataLists"));
	}
}

UNameDefinitionMap::UNameDefinitionMap()
{
}

void UNameDefinitionMap::PostLoad()
{
	Super::PostLoad();
	RegenerateDataLists();
}

void UNameDefinitionMap::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	RegenerateDataLists();
}

void UNameDefinitionMap::RegenerateDataLists()
{
	CallSignAdjectives.Empty();
	CallSignNouns.Empty();
	ShipNameAdjectives.Empty();
	ShipNameNouns.Empty();

	if(CallSignWords != nullptr)
	{
		TArray<FNameDefinitionData*> CallSigns;
		CallSignWords->GetAllRows<FNameDefinitionData>(NameDefinitionMapPrivates::RegenerateDataListsContextString, CallSigns);
		for(const FNameDefinitionData* CallSignWord : CallSigns)
		{
			if(CallSignWord->Type == ENameDefinitionType::Adjective)
			{
				CallSignAdjectives.Add(CallSignWord->Name);
			}
			else if(CallSignWord->Type == ENameDefinitionType::Noun)
			{
				CallSignNouns.Add(CallSignWord->Name);
			}
		}
	}
	
	if(ShipNameWords != nullptr)
	{
		TArray<FNameDefinitionData*> ShipNames;
		ShipNameWords->GetAllRows<FNameDefinitionData>(NameDefinitionMapPrivates::RegenerateDataListsContextString, ShipNames);
		for(const FNameDefinitionData* ShipNameWord : ShipNames)
		{
			if(ShipNameWord->Type == ENameDefinitionType::Adjective)
			{
				ShipNameAdjectives.Add(ShipNameWord->Name);
			}
			else if(ShipNameWord->Type == ENameDefinitionType::Noun)
			{
				ShipNameNouns.Add(ShipNameWord->Name);
			}
		}
	}
}
