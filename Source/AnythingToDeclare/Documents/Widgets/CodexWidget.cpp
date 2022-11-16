// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/


#include "CodexWidget.h"

#include "CodexListEntryWidget.h"
#include "Components/TreeView.h"

void UCodexWidget::PostInitProperties()
{
	Super::PostInitProperties();
	if(CodexList != nullptr)
	{
		CodexList->SetOnGetItemChildren(this, &UCodexWidget::OnGetChildren);
	}
}

void UCodexWidget::SetCodexList(const TArray<UCodexListEntryWidget*> InList) const
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
		if(UCodexListEntryWidget* ListEntry = Cast<UCodexListEntryWidget>(Entry))
		{
			OutChildren.Append(ListEntry->GetItemChildren());
		}
	}
}
