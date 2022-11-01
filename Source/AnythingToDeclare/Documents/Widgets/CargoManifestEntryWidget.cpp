﻿#include "CargoManifestEntryWidget.h"

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
	
		if(CargoWeight != nullptr)
		{
			CargoWeight->SetText(FText::AsNumber(InManifestEntry.TotalWeight * InManifestEntry.CargoType->WeightMultiplierPerUnit));
		}
	}
}
