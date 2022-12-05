#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
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
	
	FDialogueQuestionContext(const FGameplayTag& InContextSourceTag, const UObject* InLinkedAsset)
		: ContextSourceTag(InContextSourceTag)
		, LinkedData(InLinkedAsset)
	{
	}
	
	UPROPERTY()
	FGameplayTag ContextSourceTag;
	
	UPROPERTY()
	const UObject* LinkedData;
};

USTRUCT()
struct FDialogueQuestion
{
	GENERATED_BODY()
	
public:
	FDialogueQuestion()
		: HighlightedSources()
	{
	}
	
	UPROPERTY()
	TArray<FDialogueQuestionContext> HighlightedSources;
};
