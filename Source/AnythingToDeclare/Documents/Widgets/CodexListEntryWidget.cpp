// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/


#include "CodexListEntryWidget.h"

#include "AnythingToDeclare/Documents/CodexDataInterface.h"

void UCodexListEntryWidget::SetLinkedData(const UDataAsset* InData)
{
	LinkedData = InData;
	if(EntryTitle != nullptr && LinkedData != nullptr)
	{
		if(const ICodexDataInterface* DataInterface = Cast<const ICodexDataInterface>(LinkedData))
		{
			EntryTitle->SetText(FText::FromString(DataInterface->GetDataName()));
		}
	}
}
