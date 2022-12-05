#include "CargoManifestEntryWidget.h"

#include "QuestionHighlightBox.h"
#include "../CargoManifest.h"
#include "UMG/Public/Components/TextBlock.h"

void UCargoManifestEntryWidget::SetCargoManifestEntry(const FCargoManifestEntry& InManifestEntry)
{
	if(InManifestEntry.CargoType != nullptr)
	{
		if(CargoTypeName != nullptr)
		{
			CargoTypeName->SetText(FText::FromString(InManifestEntry.DisplayName));
		}

		if(CargoTypeNameHighlightBox != nullptr)
		{
			CargoTypeNameHighlightBox->SetLinkedData(InManifestEntry.DisplayedCargoType);
		}
	
		if(CargoUnits != nullptr)
		{
			CargoUnits->SetText(FText::AsNumber(InManifestEntry.TotalUnits));
		}
		
		if(CargoUnitsHighlightBox != nullptr)
		{
			CargoUnitsHighlightBox->SetLinkedData(InManifestEntry.DisplayedCargoType);
		}
	
		if(CargoWeight != nullptr)
		{
			FNumberFormattingOptions FormattingOptions;
			FormattingOptions.SetMaximumFractionalDigits(1);
			CargoWeight->SetText(FText::AsNumber(InManifestEntry.TotalUnits * InManifestEntry.DisplayWeightMultiplierPerUnit, &FormattingOptions));
		}
		
		if(CargoWeightHighlightBox != nullptr)
		{
			CargoWeightHighlightBox->SetLinkedData(InManifestEntry.DisplayedCargoType);
		}
	
		if(CargoValue != nullptr)
		{
			float ValueActual = InManifestEntry.TotalUnits * InManifestEntry.CargoType->ValuePerUnit;
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
			CargoValueHighlightBox->SetLinkedData(InManifestEntry.DisplayedCargoType);
		}
	
	}
}

void UCargoManifestEntryWidget::GetQuestionContextData(TArray<UObject*>& OutArray) const
{
	OutArray.Add(CargoTypeNameHighlightBox);
	OutArray.Add(CargoWeightHighlightBox);
	OutArray.Add(CargoValueHighlightBox);
	OutArray.Add(CargoUnitsHighlightBox);
}
