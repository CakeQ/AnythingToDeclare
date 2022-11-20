// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/


#include "CodexCargoViewWidget.h"

#include "CargoCategoryDefinition.h"
#include "CargoDefinition.h"
#include "AnythingToDeclare/Documents/Widgets/CodexListEntry.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UCodexCargoViewWidget::SetCodexEntry(const UObject* InObject)
{
	Super::SetCodexEntry(InObject);
	
	if(const UCodexListEntry* CodexEntry = Cast<const UCodexListEntry>(InObject))
	{
		if(const UCargoTypeDefinition* CargoDef = Cast<const UCargoTypeDefinition>(CodexEntry->GetLinkedData()))
		{
			WeightPerUnit = CargoDef->WeightMultiplierPerUnit;
			ValuePerUnit = CargoDef->ValuePerUnit;
		
			if(Category != nullptr && CargoDef->Category != nullptr)
			{
				Category->SetText(FText::FromString(CargoDef->Category->Name));
			}
		
			if(IsIllegal != nullptr)
			{
				IsIllegal->SetVisibility(CargoDef->IsIllegal ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
			}
		}

		ResetUnits();
	}
}

void UCodexCargoViewWidget::AdjustUnitReference(int32 InAmount)
{
	UnitReferenceValue = FMath::Clamp(UnitReferenceValue + InAmount, 1, UnitReferenceValueMax);
	RefreshUnitDisplays();
}

void UCodexCargoViewWidget::ResetUnits()
{
	UnitReferenceValue = 1;
	RefreshUnitDisplays();	
}

void UCodexCargoViewWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if(UnitAddOneButton != nullptr)
	{
		UnitAddOneButton->OnPressed.AddDynamic(this, &UCodexCargoViewWidget::AddOneUnit);
	}
	if(UnitAddTenButton != nullptr)
	{
		UnitAddTenButton->OnPressed.AddDynamic(this, &UCodexCargoViewWidget::AddTenUnits);
	}
	if(UnitAddHundredButton != nullptr)
	{
		UnitAddHundredButton->OnPressed.AddDynamic(this, &UCodexCargoViewWidget::AddHundredUnits);
	}
	if(UnitSubOneButton != nullptr)
	{
		UnitSubOneButton->OnPressed.AddDynamic(this, &UCodexCargoViewWidget::SubOneUnit);
	}
	if(UnitSubTenButton != nullptr)
	{
		UnitSubTenButton->OnPressed.AddDynamic(this, &UCodexCargoViewWidget::SubTenUnits);
	}
	if(UnitSubHundredButton != nullptr)
	{
		UnitSubHundredButton->OnPressed.AddDynamic(this, &UCodexCargoViewWidget::SubHundredUnits);
	}
	if(UnitResetButton != nullptr)
	{
		UnitResetButton->OnPressed.AddDynamic(this, &UCodexCargoViewWidget::ResetUnits);
	}
}

void UCodexCargoViewWidget::RefreshUnitDisplays()
{
	if(UnitReferenceValueView != nullptr)
	{
		UnitReferenceValueView->SetText(FText::AsNumber(UnitReferenceValue));
	}
	
	if(WeightPerUnitDisplay != nullptr)
	{
		WeightPerUnitDisplay->SetText(FText::AsNumber(WeightPerUnit * UnitReferenceValue));
	}
		
	if(ValuePerUnitDisplay != nullptr)
	{
		float ValueActual = ValuePerUnit * UnitReferenceValue;
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
		ValuePerUnitDisplay->SetText(FText::Format(FText::FromString(TEXT("{0}{1}")), FText::AsNumber(ValueActual, &FormattingOptions), FText::FromString(IsOverAMillion ? TEXT("M") : IsOverAThousand ? TEXT("K") : TEXT(""))));
	}
}

void UCodexCargoViewWidget::AddOneUnit()
{
	AdjustUnitReference(1);
}

void UCodexCargoViewWidget::AddTenUnits()
{
	AdjustUnitReference(10);
}

void UCodexCargoViewWidget::AddHundredUnits()
{
	AdjustUnitReference(100);
}

void UCodexCargoViewWidget::SubOneUnit()
{
	AdjustUnitReference(-1);
}

void UCodexCargoViewWidget::SubTenUnits()
{
	AdjustUnitReference(-10);
}

void UCodexCargoViewWidget::SubHundredUnits()
{
	AdjustUnitReference(-100);
}
