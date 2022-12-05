// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/


#include "CodexWidget.h"

#include "CodexGenericViewWidget.h"
#include "CodexListEntry.h"
#include "CodexListEntryWidget.h"
#include "Components/TreeView.h"
#include "Components/WidgetSwitcher.h"

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
			UnselectEntryAndChildren(EntryIter, Entry);
		}
	}
	if(CodexViewSwitcher != nullptr)
	{
		if(int32 EntryLayer = -1; GetEntryLayer(Entry, EntryLayer, CodexList->GetListItems()))
		{
			if(UWidget* Widget = CodexViewSwitcher->GetWidgetAtIndex(EntryLayer))
			{
				CodexViewSwitcher->SetActiveWidgetIndex(EntryLayer);
				if(UCodexGenericViewWidget* CodexViewWidget = Cast<UCodexGenericViewWidget>(Widget))
				{
					CodexViewWidget->SetCodexEntry(Entry);
				}
			}
		}
	}
}

void UCodexWidget::UnselectEntryAndChildren(UObject* Entry, const UObject* IgnoreObject)
{
	if(CodexList != nullptr && Entry != nullptr)
	{
		TArray<UObject*> Children;
		OnGetChildren(Entry, Children);

		if(Entry != IgnoreObject)
		{
			if(const UCodexListEntryWidget* EntryWidget = CodexList->GetEntryWidgetFromItem<UCodexListEntryWidget>(Entry))
			{
				EntryWidget->UnselectItem();
			}
		}
		
		for(UObject* Child : Children)
		{
			UnselectEntryAndChildren(Child, IgnoreObject);
		}
	}
}

bool UCodexWidget::GetEntryLayer(UObject* Entry, int32& LayerCount, const TArray<UObject*>& Entries)
{
	if(CodexList != nullptr && Entry != nullptr)
	{
		for(UObject* EntryIter : Entries)
		{
			if(Entry == EntryIter)
			{
				LayerCount++;
				return true;
			}
			TArray<UObject*> Children;
			OnGetChildren(EntryIter, Children);
			if(GetEntryLayer(Entry, LayerCount, Children))
			{
				LayerCount++;
				return true;
			}
		}
	}
	return false;
}


