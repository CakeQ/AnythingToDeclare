// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "QuestionTagContext.generated.h"

UENUM(BlueprintType)
enum class EQuestionTagModifier : uint8
{
	MatchingData,
};

USTRUCT(BlueprintType)
struct FQuestionTagRequirement
{
	GENERATED_BODY()

public:

	FQuestionTagRequirement()
		: TagRequirements()
	{}

	bool MeetsRequirements(const TArray<FGameplayTag>& OtherTags) const
	{
		bool MeetsRequirements = true; 
		for(const FGameplayTag& Tag : TagRequirements)
		{
			if(!OtherTags.Contains(Tag))
			{
				MeetsRequirements = false;
				break;
			}
		}
		return MeetsRequirements;
	}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FGameplayTag> TagRequirements;
};

USTRUCT(BlueprintType)
struct FQuestionTagContextData
{
	GENERATED_BODY()

public:
	FQuestionTagContextData()
		: DialogueTag()
		, PossibleTagCombinations()
		, Modifiers()
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag DialogueTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag ResponseTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FQuestionTagRequirement> PossibleTagCombinations;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FGameplayTag> RequiredRequestTags;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EQuestionTagModifier> Modifiers;
};
