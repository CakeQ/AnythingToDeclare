// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/


#include "QuestionHighlightBox.h"
#include "AnythingToDeclare/Dialogue/DialogueQuestion.h"
#include "Components/CheckBox.h"
#include "Components/TextBlock.h"

void UQuestionHighlightBox::GetQuestionContextData(FDialogueQuestion& InQuestion) const
{
	if(GetCheckedState() == ECheckBoxState::Checked)
	{
		InQuestion.HighlightedSources.Emplace(ContextTag, LinkedData, LinkedTags);
	}
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

const UObject* UQuestionHighlightBox::GetLinkedData() const
{
	return LinkedData;
}

void UQuestionHighlightBox::SetLinkedData(const UObject* InData)
{
	LinkedData = InData;
	if(!LinkedTags.IsEmpty())
	{
		LinkedTags.Empty();
	}
}

void UQuestionHighlightBox::SetLinkedData(const UObject* InData, const TArray<FGameplayTag>& InTags)
{
	LinkedData = InData;
	LinkedTags = InTags;
}

TSharedRef<SWidget> UQuestionHighlightBox::RebuildWidget()
{
	TSharedRef<SWidget> Return = Super::RebuildWidget();
	OnCheckStateChanged.AddUniqueDynamic(this, &UQuestionHighlightBox::OnCheckBoxStateChanged);
	return Return;
}
