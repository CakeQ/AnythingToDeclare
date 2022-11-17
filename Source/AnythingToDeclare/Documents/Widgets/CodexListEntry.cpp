// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/


#include "CodexListEntry.h"

#include "AnythingToDeclare/Documents/CodexDataInterface.h"

void UCodexListEntry::SetLinkedData(const UDataAsset* InData)
{
	LinkedData = InData;
}

void UCodexListEntry::AddChildEntry(UCodexListEntry* InChild)
{
	Children.Add(InChild);
}
