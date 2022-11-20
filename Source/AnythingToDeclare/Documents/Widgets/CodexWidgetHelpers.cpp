// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#include "CodexWidgetHelpers.h"

#include "CodexListEntry.h"
#include "CodexWidget.h"
#include "AnythingToDeclare/Fluff/Cargo/CargoDefinition.h"
#include "AnythingToDeclare/Fluff/Location/LocationDefinition.h"
#include "AnythingToDeclare/Fluff/Location/RegionDefinition.h"
#include "AnythingToDeclare/Fluff/Location/SubLocationDefinition.h"

void CodexWidgetHelper::GenerateCodexListFromData(UCodexWidget* CodexWidget, const TArray<UObject*>& DataEntries)
{
	if(CodexWidget != nullptr)
	{
		TArray<UCodexListEntry*> ListEntries;
		TMap<const UObject*, UCodexListEntry*> ExistingEntries;
		for(const UObject* DataEntry : DataEntries)
		{
			if(UCodexListEntry* CodexListEntry = CreateEntryForData(CodexWidget, DataEntry, ExistingEntries, nullptr))
			{
				ListEntries.AddUnique(CodexListEntry);
			}
		}
		CodexWidget->SetCodexList(ListEntries);
	}
}

void CodexWidgetHelper::GenerateCodexListFromSubLocations(UCodexWidget* CodexWidget,
	const TArray<USubLocationDefinition*>& DataEntries)
{
	if(CodexWidget != nullptr)
	{
		TArray<UCodexListEntry*> ListEntries;
		TMap<const UObject*, UCodexListEntry*> ExistingEntries;
		for(const USubLocationDefinition* DataEntry : DataEntries)
		{
			if(UCodexListEntry* CodexListEntry = CreateEntryForData(CodexWidget, DataEntry, ExistingEntries, nullptr))
			{
				ListEntries.AddUnique(CodexListEntry);
			}
		}
		CodexWidget->SetCodexList(ListEntries);
	}
}

void CodexWidgetHelper::GenerateCodexListFromCargoDefinitions(UCodexWidget* CodexWidget,
	const TArray<UCargoTypeDefinition*>& DataEntries)
{
	if(CodexWidget != nullptr)
	{
		TArray<UCodexListEntry*> ListEntries;
		TMap<const UObject*, UCodexListEntry*> ExistingEntries;
		for(const UCargoTypeDefinition* DataEntry : DataEntries)
		{
			if(UCodexListEntry* CodexListEntry = CreateEntryForData(CodexWidget, DataEntry, ExistingEntries, nullptr))
			{
				ListEntries.AddUnique(CodexListEntry);
			}
		}
		CodexWidget->SetCodexList(ListEntries);
	}
}

UCodexListEntry* CodexWidgetHelper::CreateEntryForData(UCodexWidget* CodexWidget, const UObject* DataEntry,
                                                       TMap<const UObject*, UCodexListEntry*>& ExistingEntries, UCodexListEntry* NewChildEntry)
{
	if(const ICodexDataInterface* DataInterface = Cast<const ICodexDataInterface>(DataEntry))
	{
		UCodexListEntry* CodexListEntry = nullptr;
		bool CreatedNewEntry = false;
		if(UCodexListEntry** ExistingEntry = ExistingEntries.Find(DataEntry))
		{
			if(UCodexListEntry* ExistingEntryPtr = *ExistingEntry)
			{
				CodexListEntry = ExistingEntryPtr;
				if(NewChildEntry != nullptr)
				{
					CodexListEntry->AddChildEntry(NewChildEntry);
				}
			}
		}
		else if(CodexListEntry == nullptr)
		{
			CodexListEntry = NewObject<UCodexListEntry>(CodexWidget);
			CreatedNewEntry = true;
			CodexListEntry->SetLinkedData(DataEntry);
			if(NewChildEntry != nullptr)
			{
				CodexListEntry->AddChildEntry(NewChildEntry);
			}
			ExistingEntries.Add(DataEntry, CodexListEntry);
		}
		if(const UDataAsset* ParentData = DataInterface->GetParentData())
		{
			if(UCodexListEntry* ParentListEntry = CreateEntryForData(CodexWidget, ParentData, ExistingEntries, CreatedNewEntry ? CodexListEntry : nullptr))
			{
				return ParentListEntry;
			}
		}
		return CodexListEntry;
	}
	return nullptr;
}
