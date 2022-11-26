// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/


#include "ConversationWidget.h"

#include "ConversationEntryWidget.h"
#include "Components/ScrollBox.h"

void UConversationWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if(ConversationLog != nullptr)
	{
		ConversationLog->ClearChildren();
	}
}

void UConversationWidget::AddDialogue(const FText& InText, const FText& InName, UMaterialInstance* InIcon, const bool IsPlayer)
{
	if(ConversationLog != nullptr)
	{
		UConversationEntryWidget* NewEntry = nullptr;
		if(IsPlayer && PlayerEntryWidget != nullptr)
		{
			NewEntry = CreateWidget<UConversationEntryWidget>(this, PlayerEntryWidget);
		}
		else if (NPCEntryWidget != nullptr)
		{
			NewEntry = CreateWidget<UConversationEntryWidget>(this, NPCEntryWidget);
		}
		if(NewEntry != nullptr)
		{
			NewEntry->SetText(InText);
			NewEntry->SetName(InName);
			NewEntry->SetIcon(InIcon);
			ConversationLog->AddChild(NewEntry);
			ConversationLog->ScrollToEnd();
		}
	}
}

void UConversationWidget::ClearConversation() const
{
	if(ConversationLog != nullptr)
	{
		ConversationLog->ClearChildren();
	}
}
