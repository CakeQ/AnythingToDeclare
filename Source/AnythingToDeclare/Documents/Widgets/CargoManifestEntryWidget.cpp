#include "CargoManifestEntryWidget.h"

#include "../CargoManifest.h"
#include "UMG/Public/Components/TextBlock.h"

void UCargoManifestEntryWidget::SetCargoManifestEntry(const FCargoManifestEntry& InManifestEntry)
{
	if(InManifestEntry.CargoType != nullptr)
	{
		if(CargoTypeName != nullptr)
		{
			CargoTypeName->SetText(FText::FromString(InManifestEntry.CargoType->Name));
		}
	
		if(CargoUnits != nullptr)
		{
			CargoUnits->SetText(FText::AsNumber(InManifestEntry.TotalUnits));
		}
		
		if(CargoWeight != nullptr)
		{
			CargoWeight->SetText(FText::AsNumber(InManifestEntry.TotalUnits * InManifestEntry.CargoType->WeightMultiplierPerUnit));
		}
		
		if(CargoValue != nullptr)
		{
			CargoValue->SetText(FText::AsNumber(InManifestEntry.TotalUnits * InManifestEntry.CargoType->ValuePerUnit));
		}
	}
}
