// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#include "CodexWidgetHelpers.h"

#include "CodexListEntry.h"
#include "CodexWidget.h"
#include "AnythingToDeclare/Fluff/Location/LocationDefinition.h"
#include "AnythingToDeclare/Fluff/Location/RegionDefinition.h"
#include "AnythingToDeclare/Fluff/Location/SubLocationDefinition.h"

void CodexWidgetHelper::GenerateCodexListFromRegions(UCodexWidget* CodexWidget,
                                                     const TArray<USubLocationDefinition*> SubLocations)
{
	TArray<UCodexListEntry*> ListEntries;
	TMap<const ULocationDefinition*, UCodexListEntry*> LocationWidgets;
	TMap<const URegionDefinition*, UCodexListEntry*> RegionWidgets;
	
	for(const USubLocationDefinition* SubLocation : SubLocations)
	{
		UCodexListEntry* SubLocationWidget = NewObject<UCodexListEntry>(CodexWidget);
		SubLocationWidget->SetLinkedData(SubLocation);
		if(SubLocation->Location != nullptr)
		{
			UCodexListEntry* LocationWidget = nullptr;
			if(UCodexListEntry** Location = LocationWidgets.Find(SubLocation->Location))
			{
				if(UCodexListEntry* LocationPtr = *Location)
				{
					LocationWidget = LocationPtr;
				}
			}
			else
			{
				LocationWidget = NewObject<UCodexListEntry>(CodexWidget);
				LocationWidget->SetLinkedData(SubLocation->Location);
				LocationWidgets.Add(SubLocation->Location, LocationWidget);
				if(SubLocation->Location->Region != nullptr)
				{
					UCodexListEntry* RegionWidget = nullptr;
					if(UCodexListEntry** Region = RegionWidgets.Find(SubLocation->Location->Region))
					{
						if(UCodexListEntry* RegionPtr = *Region)
						{
							RegionWidget = RegionPtr;
						}
					}
					else
					{
						RegionWidget = NewObject<UCodexListEntry>(CodexWidget);
						RegionWidget->SetLinkedData(SubLocation->Location->Region);
						RegionWidgets.Add(SubLocation->Location->Region, RegionWidget);
						ListEntries.Add(RegionWidget);
					}
					if(RegionWidget != nullptr)
					{
						RegionWidget->AddChildEntry(LocationWidget);
					}
				}
			}
			if(LocationWidget != nullptr)
			{
				LocationWidget->AddChildEntry(SubLocationWidget);
			}
		}
	}
	CodexWidget->SetCodexList(ListEntries);
}
