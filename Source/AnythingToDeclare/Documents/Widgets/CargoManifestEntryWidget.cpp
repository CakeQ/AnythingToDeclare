#include "CargoManifestEntryWidget.h"

#include "QuestionHighlightBox.h"
#include "../CargoManifest.h"
#include "UMG/Public/Components/TextBlock.h"

void UCargoManifestEntryWidget::SetCargoManifestEntry(const FCargoManifestEntry& InManifestEntry)
{
	if(CargoTypeName != nullptr)
	{
		CargoTypeName->SetText(FText::FromString(InManifestEntry.DisplayName.Value));
	}

	if(CargoTypeNameHighlightBox != nullptr)
	{
		CargoTypeNameHighlightBox->SetLinkedData(InManifestEntry.DisplayName.LinkedData, InManifestEntry.DisplayName.Tags);
	}

	if(CargoUnits != nullptr)
	{
		CargoUnits->SetText(FText::AsNumber(InManifestEntry.TotalUnits.Value));
	}
	
	if(CargoUnitsHighlightBox != nullptr)
	{
		CargoUnitsHighlightBox->SetLinkedData(InManifestEntry.TotalUnits.LinkedData, InManifestEntry.TotalUnits.Tags);
	}

	if(CargoWeight != nullptr)
	{
		FNumberFormattingOptions FormattingOptions;
		FormattingOptions.SetMaximumFractionalDigits(1);
		CargoWeight->SetText(FText::AsNumber(InManifestEntry.TotalUnits.Value * InManifestEntry.DisplayWeightMultiplier.Value, &FormattingOptions));
	}
	
	if(CargoWeightHighlightBox != nullptr)
	{
		CargoWeightHighlightBox->SetLinkedData(InManifestEntry.DisplayWeightMultiplier.LinkedData, InManifestEntry.DisplayWeightMultiplier.Tags);
	}

	if(CargoValue != nullptr)
	{
		float ValueActual = InManifestEntry.TotalUnits.Value * InManifestEntry.DisplayValueMultiplier.Value;
		bool IsOverAMillion = false;
		bool IsOverAThousand = false;

		if(ValueActual >= 1000000.0f)
		{
			ValueActual /= 1000000.0f;
			IsOverAMillion = true;
		}
		else if(ValueActual >= 1000.0f)
		{
			ValueActual /= 1000.0f;
			IsOverAThousand = true;
		}

		FNumberFormattingOptions FormattingOptions;
		FormattingOptions.SetMinimumFractionalDigits(IsOverAThousand ? 0 : 2);
		FormattingOptions.SetMaximumFractionalDigits(IsOverAThousand ? 1 : 2);
		CargoValue->SetText(FText::Format(FText::FromString(TEXT("{0}{1}")), FText::AsNumber(ValueActual, &FormattingOptions), FText::FromString(IsOverAMillion ? TEXT("M") : IsOverAThousand ? TEXT("K") : TEXT(""))));
	}
	
	if(CargoValueHighlightBox != nullptr)
	{
		CargoValueHighlightBox->SetLinkedData(InManifestEntry.DisplayValueMultiplier.LinkedData, InManifestEntry.DisplayValueMultiplier.Tags);
	}
}

void UCargoManifestEntryWidget::GetQuestionContextData(TArray<UObject*>& OutArray) const
{
	OutArray.Add(CargoTypeNameHighlightBox);
	OutArray.Add(CargoWeightHighlightBox);
	OutArray.Add(CargoValueHighlightBox);
	OutArray.Add(CargoUnitsHighlightBox);
}
