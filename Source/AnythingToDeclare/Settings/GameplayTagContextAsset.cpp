// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#include "GameplayTagContextAsset.h"

#include "QuestionTagContext.h"
#include "RequestTagContext.h"
#include "AnythingToDeclare/Dialogue/DialogueQuestion.h"

const FGameplayTagContextData* UGameplayTagContextAsset::FindRequestTagContextData(const FGameplayTag& RequestTag) const
{
	for(const FGameplayTagContextData& TagContextData : RequestModifiers)
	{
		if(TagContextData.Tag.MatchesTag(RequestTag))
		{
			return &TagContextData;
		}
	}
	return nullptr;
}

const FQuestionTagContextData* UGameplayTagContextAsset::FindQuestionTagContextData(
	const FDialogueQuestion& QuestionRequest) const
{
	bool MatchingData = true;
	if(QuestionRequest.HighlightedSources.Num() > 1)
	{
		for(int32 i = 1; i < QuestionRequest.HighlightedSources.Num(); i++)
		{
			const FDialogueQuestionContext& CurrentContext = QuestionRequest.HighlightedSources[i];
			const FDialogueQuestionContext& PreviousContext = QuestionRequest.HighlightedSources[i - 1];

			if(CurrentContext.LinkedData != PreviousContext.LinkedData)
			{
				MatchingData = false;
			}
		}
	}

	for(const FQuestionTagContextData& QuestionData : QuestionContexts)
	{
		if(QuestionData.Modifiers.Contains(EQuestionTagModifier::MatchingData) && !MatchingData)
		{
			continue;
		}

		bool MatchingTags = true;
		for(const FGameplayTag& RequirementTag : QuestionData.TagRequirements)
		{
			if(!QuestionRequest.HighlightedSources.FindByPredicate([RequirementTag](const FDialogueQuestionContext& Context){ return Context.ContextSourceTag == RequirementTag; }))
			{
				MatchingTags = false;
				break;
			}
		}

		if(MatchingTags)
		{
			return &QuestionData;
		}
	}
	
	return nullptr;
}
