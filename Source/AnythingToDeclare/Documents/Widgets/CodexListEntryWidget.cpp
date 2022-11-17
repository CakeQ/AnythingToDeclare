// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/


#include "CodexListEntryWidget.h"

#include "CodexListEntry.h"
#include "CodexWidget.h"
#include "AnythingToDeclare/Documents/CodexDataInterface.h"
#include "Components/CheckBox.h"
#include "Components/TreeView.h"
#include "Components/ListViewBase.h"

void UCodexListEntryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if(EntryExpansion != nullptr)
	{
		EntryExpansion->OnCheckStateChanged.AddDynamic(this, &UCodexListEntryWidget::OnExpansionStateChanged);
	}
	
	if(EntrySelection != nullptr)
	{
		EntrySelection->OnCheckStateChanged.AddDynamic(this, &UCodexListEntryWidget::OnSelectionStateChanged);
	}
	
	if(const UObject* OwningWidget = GetOuter())
	{
		if(UObject* OwningOwningWidget = OwningWidget->GetOuter())
		{
			if(UCodexWidget* CodexWidget = Cast<UCodexWidget>(OwningOwningWidget))
			{
				OnExpansionUpdated.AddDynamic(CodexWidget, &UCodexWidget::UpdateListEntryExpansion);
				OnSelectedEvent.AddDynamic(CodexWidget, &UCodexWidget::SetActiveEntry);
			}
		}
	}
}

void UCodexListEntryWidget::OnExpansionStateChanged(const bool bBIsChecked)
{
	OnExpansionUpdated.Broadcast(LinkedData, bBIsChecked);
}

void UCodexListEntryWidget::NativeOnItemSelectionChanged(bool bIsSelected)
{
	IUserListEntry::NativeOnItemSelectionChanged(bIsSelected);
	if(EntrySelection != nullptr)
	{
		EntrySelection->SetCheckedState(bIsSelected ? ECheckBoxState::Checked: ECheckBoxState::Unchecked);
	}
}

void UCodexListEntryWidget::OnSelectionStateChanged(bool bBIsChecked)
{
	if(bBIsChecked)
	{
		OnSelectedEvent.Broadcast(LinkedData);
	}
}

void UCodexListEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
		
	if(UCodexListEntry* CodexListEntry = Cast<UCodexListEntry>(ListItemObject))
	{
		LinkedData = CodexListEntry;
		if(const ICodexDataInterface* DataInterface = Cast<const ICodexDataInterface>(CodexListEntry->GetLinkedData()))
		{
			if(EntryTitle != nullptr)
			{
				EntryTitle->SetText(FText::FromString(DataInterface->GetDataName()));
			}
			if(EntryExpansion != nullptr)
			{
				EntryExpansion->SetVisibility(CodexListEntry->GetItemChildren().IsEmpty() ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
			}
		}
	}
}
