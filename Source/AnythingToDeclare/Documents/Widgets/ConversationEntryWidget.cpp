// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/


#include "ConversationEntryWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UConversationEntryWidget::SetText(const FText& InText) const
{
	if(Dialogue != nullptr)
	{
		Dialogue->SetText(InText);
	}
}

void UConversationEntryWidget::SetName(const FText& InText)
{
	if(Nameplate != nullptr)
	{
		Nameplate->SetText(InText);
	}
}

void UConversationEntryWidget::SetIcon(UMaterialInstance* InIcon) const
{
	if(Portrait != nullptr)
	{
		Portrait->SetBrushFromMaterial(InIcon);
	}
}
