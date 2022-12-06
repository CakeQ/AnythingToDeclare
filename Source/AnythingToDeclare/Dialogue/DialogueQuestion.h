#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "AnythingToDeclare/Settings/RequestTagContext.h"
#include "UObject/ObjectMacros.h"

#include "DialogueQuestion.generated.h"

class UQuestionHighlightBox;
class UQuestionHighlightWidget;

USTRUCT()
struct FDialogueQuestionContext
{
	GENERATED_BODY()
public:

	FDialogueQuestionContext()
		: ContextSourceTag()
		, LinkedData()
	{
	}
	
	FDialogueQuestionContext(const FGameplayTag& InContextSourceTag, const UObject* InLinkedAsset, const TArray<FGameplayTag>& InTags)
		: ContextSourceTag(InContextSourceTag)
		, LinkedData(InLinkedAsset)
		, Tags(InTags)
	{
	}
	
	UPROPERTY()
	FGameplayTag ContextSourceTag;

	UPROPERTY()
	const UObject* LinkedData;
	
	UPROPERTY()
	TArray<FGameplayTag> Tags;
};

USTRUCT()
struct FDialogueQuestion
{
	GENERATED_BODY()
	
public:
	FDialogueQuestion()
		: HighlightedSources()
		, RequestTags()
	{
	}
	
	UPROPERTY()
	TArray<FDialogueQuestionContext> HighlightedSources;

	UPROPERTY()
	TArray<FGameplayTag> RequestTags;
};
