#include "CargoManifestEntryWidget.h"

#include "../CargoManifest.h"
#include "UMG/Public/Components/TextBlock.h"

void UCargoManifestEntryWidget::SetCargoManifestEntry(const FCargoManifestEntry& InManifestEntry)
{
	if(CargoTypeName != nullptr)
	{
		CargoTypeName->SetText(FText::FromString(InManifestEntry.CargoType));
	}
	
	if(CargoWeight != nullptr)
	{
		CargoWeight->SetText(FText::AsNumber(InManifestEntry.TotalWeight) + TEXT("T"));
	}
}
