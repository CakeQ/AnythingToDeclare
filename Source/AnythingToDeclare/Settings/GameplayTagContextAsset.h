// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "QuestionTagContext.h"
#include "RequestTagContext.h"
#include "UObject/Object.h"
#include "GameplayTagContextAsset.generated.h"

struct FDialogueQuestion;

/**
 * 
 */
UCLASS()
class ANYTHINGTODECLARE_API UGameplayTagContextAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	const FGameplayTagContextData* FindRequestTagContextData(const FGameplayTag& RequestTag) const;
	const FQuestionTagContextData* FindQuestionTagContextData(const FDialogueQuestion& QuestionRequest) const;
	
	UPROPERTY(EditDefaultsOnly, Category="Dialogue")
	FGameplayTag GreetingTag;
	
	UPROPERTY(EditDefaultsOnly, Category="Requests")
	TArray<FGameplayTagContextData> RequestModifiers;
	
	UPROPERTY(EditDefaultsOnly, Category="Questions")
	TArray<FQuestionTagContextData> QuestionContexts;
};
