// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/


#include "CodexGenericViewWidget.h"

#include "CodexListEntry.h"
#include "AnythingToDeclare/Documents/CodexDataInterface.h"
#include "Components/Image.h"
#include "UMG/Public/Components/TextBlock.h"

void UCodexGenericViewWidget::SetCodexEntry(const UObject* InObject) const
{
	if(const UCodexListEntry* CodexEntry = Cast<const UCodexListEntry>(InObject))
	{
		if(const ICodexDataInterface* CodexData = Cast<const ICodexDataInterface>(CodexEntry->GetLinkedData()))
		{
			if(EntryName != nullptr)
			{
				EntryName->SetText(FText::FromString(CodexData->GetDataName()));
			}

			if(EntryDescription != nullptr)
			{
				EntryDescription->SetText(FText::FromString(CodexData->GetDescription()));
			}

			if(EntryIcon != nullptr)
			{
				EntryIcon->SetBrushFromMaterial(CodexData->GetIcon());
			}
		}
	}
}
