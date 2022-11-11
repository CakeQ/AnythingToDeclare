#include "CargoManifestWidget.h"

#include "CargoManifestEntryWidget.h"
#include "../CargoManifest.h"
#include "UMG/Public/Components/TextBlock.h"

void UCargoManifestWidget::SetCargoManifest(const FCargoManifest& InManifest)
{
	if(ShipName != nullptr)
	{
		ShipName->SetText(FText::FromString(InManifest.ShipName));
	}

	if(OriginPlanet != nullptr)
	{
		OriginPlanet->SetText(FText::FromString(InManifest.OriginLocation));
	}

	if(OriginSubLocation != nullptr)
	{
		OriginSubLocation->SetText(FText::FromString(InManifest.OriginSubLocation));
	}

	if(DestinationPlanet != nullptr)
	{
		DestinationPlanet->SetText(FText::FromString(InManifest.DestinationLocation));
	}

	if(DestinationSubLocation != nullptr)
	{
		DestinationSubLocation->SetText(FText::FromString(InManifest.DestinationSubLocation));
	}

	if(CargoManifestEntries != nullptr)
	{
		CargoManifestEntries->ClearChildren();
		CargoManifestEntries->ScrollToStart();
		for(const FCargoManifestEntry& Entry : InManifest.Cargo)
		{
			UCargoManifestEntryWidget* NewEntry = CreateWidget<UCargoManifestEntryWidget>(this, CargoManifestEntryWidgetClass);
			NewEntry->SetCargoManifestEntry(Entry);
			CargoManifestEntries->AddChild(NewEntry);
		}
	}
}
