#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"

#include "DialogueMessage.generated.h"

USTRUCT()
struct FDialogueMessage
{
	GENERATED_BODY()
public:

	FDialogueMessage()
		: DialogueText()
		, DisplayName()
		, DialogueIcon(nullptr)
		, IsPlayer(false)
	{
	}
	
	FDialogueMessage(const FText& InText, const FText& InName, UMaterialInstance* InIcon, const bool InIsPlayer)
		: DialogueText(InText)
		, DisplayName(InName)
		, DialogueIcon(InIcon)
		, IsPlayer(InIsPlayer)
	{
	}
	
	UPROPERTY()
	FText DialogueText;

	UPROPERTY()
	FText DisplayName;

	UPROPERTY()
	UMaterialInstance* DialogueIcon;

	UPROPERTY(EditAnywhere)
	bool IsPlayer;
};
