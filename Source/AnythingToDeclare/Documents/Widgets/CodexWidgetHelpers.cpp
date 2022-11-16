// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#include "CodexWidgetHelpers.h"

#include "CodexListEntryWidget.h"
#include "CodexWidget.h"
#include "AnythingToDeclare/Fluff/Location/LocationDefinition.h"
#include "AnythingToDeclare/Fluff/Location/RegionDefinition.h"
#include "AnythingToDeclare/Fluff/Location/SubLocationDefinition.h"
#include "Components/TreeView.h"

void CodexWidgetHelper::GenerateCodexListFromRegions(UCodexWidget* CodexWidget,
                                                     const TArray<USubLocationDefinition*> SubLocations)
{
	TArray<UCodexListEntryWidget*> ListEntries;
	TMap<const ULocationDefinition*, UCodexListEntryWidget*> LocationWidgets;
	TMap<const URegionDefinition*, UCodexListEntryWidget*> RegionWidgets;
	
	for(const USubLocationDefinition* SubLocation : SubLocations)
	{
		UCodexListEntryWidget* SubLocationWidget = CreateWidget<UCodexListEntryWidget>(CodexWidget, CodexWidget->CodexList->GetEntryWidgetClass());
		SubLocationWidget->SetLinkedData(SubLocation);
		if(SubLocation->Location != nullptr)
		{
			UCodexListEntryWidget* LocationWidget = nullptr;
			if(UCodexListEntryWidget** Location = LocationWidgets.Find(SubLocation->Location))
			{
				if(UCodexListEntryWidget* LocationPtr = *Location)
				{
					LocationWidget = LocationPtr;
				}
			}
			else
			{
				LocationWidget = CreateWidget<UCodexListEntryWidget>(CodexWidget, CodexWidget->CodexList->GetEntryWidgetClass());
				LocationWidget->SetLinkedData(SubLocation->Location);
				LocationWidgets.Add(SubLocation->Location, LocationWidget);
				if(SubLocation->Location->Region != nullptr)
				{
					UCodexListEntryWidget* RegionWidget = nullptr;
					if(UCodexListEntryWidget** Region = RegionWidgets.Find(SubLocation->Location->Region))
					{
						if(UCodexListEntryWidget* RegionPtr = *Region)
						{
							RegionWidget = RegionPtr;
						}
					}
					else
					{
						RegionWidget = CreateWidget<UCodexListEntryWidget>(CodexWidget, CodexWidget->CodexList->GetEntryWidgetClass());
						RegionWidget->SetLinkedData(SubLocation->Location->Region);
						RegionWidgets.Add(SubLocation->Location->Region, RegionWidget);
						ListEntries.Add(RegionWidget);
					}
					if(RegionWidget != nullptr)
					{
						RegionWidget->Children.Add(LocationWidget);
					}
				}
			}
			if(LocationWidget != nullptr)
			{
				LocationWidget->Children.Add(SubLocationWidget);
			}
		}
	}
	CodexWidget->SetCodexList(ListEntries);
}
