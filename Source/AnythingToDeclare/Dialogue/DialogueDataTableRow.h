#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

#include <Engine/DataTable.h>

#include "DialogueDataTableRow.generated.h"

USTRUCT(BlueprintType)
struct FDialogueDataTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:

	FDialogueDataTableRow()
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag DialogueTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Dialogue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag Requirement;
};
