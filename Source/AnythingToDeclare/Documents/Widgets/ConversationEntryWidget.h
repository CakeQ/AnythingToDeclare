// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UObject/Object.h"
#include "ConversationEntryWidget.generated.h"

class UImage;
class UTextBlock;

/**
 * 
 */
UCLASS()
class ANYTHINGTODECLARE_API UConversationEntryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetText(const FText& InText) const;
	void SetName(const FText& InText);
	void SetIcon(UMaterialInstance* InIcon) const;

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Dialogue;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Nameplate;

	UPROPERTY(meta = (BindWidget))
	UImage* Portrait;
};
