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
struct FQuestionTagContextData
{
	GENERATED_BODY()

public:

	FQuestionTagContextData()
		: DialogueTag()
		, TagRequirements()
		, Modifiers()
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Name)
	FGameplayTag DialogueTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Name)
	FGameplayTag ResponseTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Name)
	TArray<FGameplayTag> TagRequirements;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Name)
	TArray<EQuestionTagModifier> Modifiers;
};
