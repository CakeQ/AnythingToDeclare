// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "AnythingToDeclare/Dialogue/DialogueQuestion.h"

#include "QuestionContextInterface.generated.h"

struct FGameplayTag;

UINTERFACE()
class ANYTHINGTODECLARE_API UQuestionContextInterface : public UInterface
{
	GENERATED_BODY()
};

class ANYTHINGTODECLARE_API IQuestionContextInterface
{
	GENERATED_IINTERFACE_BODY()

public:
	UFUNCTION()
	virtual void GetQuestionContextData(FDialogueQuestion& InQuestion) const = 0;
	
	UFUNCTION()
	virtual void SetRequestTags(const TArray<FGameplayTag>& InTags) = 0;

	UFUNCTION()
	virtual void BindQuestionHighlighting(UObject* InObject, const FName& InFunctionName) = 0;
};
