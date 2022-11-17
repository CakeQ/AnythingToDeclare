// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/


#include "CodexWidget.h"

#include "CodexGenericViewWidget.h"
#include "CodexListEntry.h"
#include "Components/TreeView.h"

void UCodexWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if(CodexList != nullptr)
	{
		CodexList->SetOnGetItemChildren(this, &UCodexWidget::OnGetChildren);
	}
}

void UCodexWidget::SetCodexList(const TArray<UCodexListEntry*>& InList) const
{
	if(CodexList != nullptr)
	{
		CodexList->SetListItems(InList);
	}
}

void UCodexWidget::OnGetChildren(UObject* Entry, TArray<UObject*>& OutChildren)
{
	if(Entry != nullptr)
	{
		if(const UCodexListEntry* ListEntry = Cast<UCodexListEntry>(Entry))
		{
			OutChildren.Append(ListEntry->GetItemChildren());
		}
	}
}

void UCodexWidget::UpdateListEntryExpansion(UObject* Entry, const bool bIsExpanded)
{
	CodexList->SetItemExpansion(Entry, bIsExpanded);
}

void UCodexWidget::SetActiveEntry(UObject* Entry)
{
	if(CodexList != nullptr)
	{
		for(UObject* EntryIter : CodexList->GetListItems())
		{
			if(EntryIter != Entry)
			{
				CodexList->SetItemSelection(EntryIter, false);
			}
		}
	}
	if(CodexView != nullptr)
	{
		CodexView->SetCodexEntry(Entry);
	}
}
