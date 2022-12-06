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
	TArray<FGameplayTag> SourceTags;
	TArray<FGameplayTag> SourceRequestTags;
	if(QuestionRequest.HighlightedSources.Num() > 1)
	{
		for(int32 i = 0; i < QuestionRequest.HighlightedSources.Num(); i++)
		{
			const FDialogueQuestionContext& CurrentContext = QuestionRequest.HighlightedSources[i];
			if(i > 0)
			{
				if(const FDialogueQuestionContext& PreviousContext = QuestionRequest.HighlightedSources[i - 1]; CurrentContext.LinkedData != PreviousContext.LinkedData)
				{
					MatchingData = false;
				}
			}
			SourceTags.Add(CurrentContext.ContextSourceTag);
			SourceRequestTags.Append(CurrentContext.Tags);
		}
	}

	for(const FQuestionTagContextData& QuestionData : QuestionContexts)
	{
		if(QuestionData.Modifiers.Contains(EQuestionTagModifier::MatchingData) && !MatchingData)
		{
			continue;
		}

		bool MatchingTags = false;
		for(const FQuestionTagRequirement& RequirementTag : QuestionData.PossibleTagCombinations)
		{
			if(RequirementTag.MeetsRequirements(SourceTags))
			{
				MatchingTags = true;
				break;
			}
		}

		bool MatchingRequestTags = true;
		for(const FGameplayTag& RequirementTag : QuestionData.RequiredRequestTags)
		{
			if(!SourceRequestTags.Contains(RequirementTag))
			{
				MatchingRequestTags = false;
				break;
			}
		}

		if(MatchingTags && MatchingRequestTags)
		{
			return &QuestionData;
		}
	}
	
	return nullptr;
}
