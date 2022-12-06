#include "CargoManifestWidget.h"

#include "CargoManifestEntryWidget.h"
#include "QuestionHighlightBox.h"
#include "../CargoManifest.h"
#include "AnythingToDeclare/Fluff/Location/SubLocationDefinition.h"
#include "AnythingToDeclare/Settings/RequestTagContext.h"
#include "Components/ScrollBox.h"
#include "UMG/Public/Components/TextBlock.h"

void UCargoManifestWidget::SetCargoManifest(const FCargoManifest& InManifest)
{
	if(ShipName != nullptr)
	{
		ShipName->SetText(FText::FromString(InManifest.ShipName));
	}

	if(OriginPlanet != nullptr)
	{
		OriginPlanet->SetText(FText::FromString(InManifest.OriginLocation.Value));
		if(OriginPlanetHighlightBox != nullptr)
		{
			OriginPlanetHighlightBox->SetLinkedData(InManifest.OriginLocation.LinkedData, InManifest.OriginLocation.Tags);
		}
	}

	if(OriginSubLocation != nullptr)
	{
		OriginSubLocation->SetText(FText::FromString(InManifest.OriginSubLocation.Value));
		if(OriginSubLocationHighlightBox != nullptr)
		{
			OriginSubLocationHighlightBox->SetLinkedData(InManifest.OriginSubLocation.LinkedData, InManifest.OriginSubLocation.Tags);
		}
	}

	if(DestinationPlanet != nullptr)
	{
		DestinationPlanet->SetText(FText::FromString(InManifest.DestinationLocation.Value));
		if(DestinationPlanetHighlightBox != nullptr)
		{
			DestinationPlanetHighlightBox->SetLinkedData(InManifest.DestinationLocation.LinkedData, InManifest.DestinationLocation.Tags);
		}
	}

	if(DestinationSubLocation != nullptr)
	{
		DestinationSubLocation->SetText(FText::FromString(InManifest.DestinationSubLocation.Value));
		if(DestinationSubLocationHighlightBox != nullptr)
		{
			DestinationSubLocationHighlightBox->SetLinkedData(InManifest.DestinationSubLocation.LinkedData, InManifest.DestinationSubLocation.Tags);
		}
	}

	if(CargoManifestEntries != nullptr)
	{
		CargoManifestEntries->ClearChildren();
		CargoManifestEntries->ScrollToStart();
		for(const FCargoManifestEntry& Entry : InManifest.Cargo)
		{
			if(Entry.Modifiers.Contains(EGameplayTagModifier::HiddenPartially) || Entry.Modifiers.Contains(EGameplayTagModifier::HiddenFully))
			{
				continue;
			}
			UCargoManifestEntryWidget* NewEntry = CreateWidget<UCargoManifestEntryWidget>(this, CargoManifestEntryWidgetClass);
			NewEntry->SetCargoManifestEntry(Entry);
			CargoManifestEntries->AddChild(NewEntry);
		}
	}

	if(CargoWeightTotal != nullptr)
	{
		float WeightTotal = 0.0f;
		for(const FCargoManifestEntry& Entry : InManifest.Cargo)
		{
			if(Entry.Modifiers.Contains(EGameplayTagModifier::HiddenFully))
			{
				continue;
			}
			WeightTotal += Entry.TotalUnits.Value * Entry.DisplayWeightMultiplier.Value;
		}
		FNumberFormattingOptions FormattingOptions;
		FormattingOptions.SetMaximumFractionalDigits(1);
		CargoWeightTotal->SetText(FText::AsNumber(WeightTotal, &FormattingOptions));
	}
}

void UCargoManifestWidget::GetQuestionContextData(TArray<UObject*>& OutArray) const
{
	OutArray.Add(OriginPlanetHighlightBox);
	OutArray.Add(OriginSubLocationHighlightBox);
	OutArray.Add(DestinationPlanetHighlightBox);
	OutArray.Add(DestinationSubLocationHighlightBox);
	OutArray.Add(CargoWeightTotalHighlightBox);
}
