// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/


#include "CustomsRequestCodexMonitorWidget.h"

#include "AnythingToDeclare/Documents/Widgets/CodexWidget.h"
#include "Components/WidgetSwitcher.h"

UCustomsRequestCodexMonitorWidget::UCustomsRequestCodexMonitorWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCustomsRequestCodexMonitorWidget::TryToFindAndShowData(const UObject* InData) const
{
	if(CodexSwitcher != nullptr && InData != nullptr)
	{
		if(CargoCodex != nullptr && CargoCodex->TryToFindAndShowData(InData))
		{
			CodexSwitcher->SetActiveWidget(CargoCodex);	
		}
		else if(LocationCodex != nullptr && LocationCodex->TryToFindAndShowData(InData))
		{
			CodexSwitcher->SetActiveWidget(LocationCodex);	
		}
	}
}
