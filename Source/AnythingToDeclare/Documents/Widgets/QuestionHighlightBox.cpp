// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/


#include "QuestionHighlightBox.h"
#include "AnythingToDeclare/Dialogue/DialogueQuestion.h"
#include "Components/CheckBox.h"
#include "Components/TextBlock.h"

void UQuestionHighlightBox::GetQuestionContextData(FDialogueQuestion& InQuestion) const
{
	if(GetCheckedState() == ECheckBoxState::Checked)
	{
		InQuestion.HighlightedSources.Emplace(ContextTag, LinkedData);
	}
}

void UQuestionHighlightBox::SetRequestTags(const TArray<FGameplayTag>& InTags)
{
	SetHighlightableState(InTags);
}

void UQuestionHighlightBox::BindQuestionHighlighting(UObject* InObject, const FName& InFunctionName)
{
	if(!OnHighlightChanged.IsBound())
	{
		OnHighlightChanged.BindUFunction(InObject, InFunctionName);
	}
}

void UQuestionHighlightBox::OnCheckBoxStateChanged(bool bBIsChecked)
{
	OnHighlightChanged.ExecuteIfBound(GetCheckedState() == ECheckBoxState::Checked, this);
}

const UObject* UQuestionHighlightBox::GetLinkedData()
{
	return LinkedData;
}

void UQuestionHighlightBox::SetLinkedData(const UObject* InData)
{
	LinkedData = InData;
}

void UQuestionHighlightBox::SetHighlightableState(const TArray<FGameplayTag>& InRequestTags)
{
	bool IsHighlightable = true;
	for(const FGameplayTag& Tag : RequestTagsThatAllowHighlighting)
	{
		if(!InRequestTags.Contains(Tag))
		{
			IsHighlightable = false;
		}
	}
	SetVisibility(IsHighlightable ? ESlateVisibility::Visible : ESlateVisibility::HitTestInvisible);
}

TSharedRef<SWidget> UQuestionHighlightBox::RebuildWidget()
{
	TSharedRef<SWidget> Return = Super::RebuildWidget();
	OnCheckStateChanged.AddDynamic(this, &UQuestionHighlightBox::OnCheckBoxStateChanged);
	return Return;
}
