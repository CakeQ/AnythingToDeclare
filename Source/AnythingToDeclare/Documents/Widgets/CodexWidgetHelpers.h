// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#pragma once

#include "CoreMinimal.h"

class UCargoTypeDefinition;
class UCodexListEntry;
class USubLocationDefinition;
class UCodexWidget;

namespace CodexWidgetHelper
{
	void GenerateCodexListFromData(UCodexWidget* CodexWidget, const TArray<UObject*>& DataEntries);
	void GenerateCodexListFromSubLocations(UCodexWidget* CodexWidget, const TArray<USubLocationDefinition*>& DataEntries);
	void GenerateCodexListFromCargoDefinitions(UCodexWidget* CodexWidget, const TArray<UCargoTypeDefinition*>& DataEntries);
	UCodexListEntry* CreateEntryForData(UCodexWidget* CodexWidget, const UObject* DataEntry, TMap<const UObject*,
		UCodexListEntry*>& ExistingEntries, UCodexListEntry* NewChildEntry);
}
