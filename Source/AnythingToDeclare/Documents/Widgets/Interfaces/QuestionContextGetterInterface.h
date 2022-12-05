// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "QuestionContextGetterInterface.generated.h"

struct FGameplayTag;

UINTERFACE()
class ANYTHINGTODECLARE_API UQuestionContextGetterInterface : public UInterface
{
	GENERATED_BODY()
};

class ANYTHINGTODECLARE_API IQuestionContextGetterInterface
{
	GENERATED_IINTERFACE_BODY()

public:
	UFUNCTION()
	virtual void GetQuestionContextData(TArray<UObject*>& OutArray) const = 0;
};
