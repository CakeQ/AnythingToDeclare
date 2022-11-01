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
		OriginPlanet->SetText(FText::FromString(InManifest.OriginPlanet));
	}

	if(DestinationPlanet != nullptr)
	{
		DestinationPlanet->SetText(FText::FromString(InManifest.DestinationPlanet));
	}

	if(CargoManifestEntries != nullptr)
	{
		CargoManifestEntries->ClearChildren();
		for(const FCargoManifestEntry& Entry : InManifest.Cargo)
		{
			UCargoManifestEntryWidget* NewEntry = CreateWidget<UCargoManifestEntryWidget>(this, CargoManifestEntryWidgetClass);
			NewEntry->SetCargoManifestEntry(Entry);
			CargoManifestEntries->AddChildToVerticalBox(NewEntry);
		}
	}
}
