#include "CargoManifestEntryWidget.h"

#include "../CargoManifest.h"
#include "UMG/Public/Components/TextBlock.h"

void UCargoManifestEntryWidget::SetCargoManifestEntry(const FCargoManifestEntry& InManifestEntry)
{
	if(CargoTypeName != nullptr)
	{
		if(InManifestEntry.CargoType != nullptr)
		{
			CargoTypeName->SetText(FText::FromString(InManifestEntry.CargoType->Name));
		}
	
		if(CargoWeight != nullptr)
		{
			CargoWeight->SetText(FText::FromString(FString(TEXT("%iT"), InManifestEntry.TotalWeight * InManifestEntry.CargoType->WeightMultiplierPerUnit)));
		}
	}
}
