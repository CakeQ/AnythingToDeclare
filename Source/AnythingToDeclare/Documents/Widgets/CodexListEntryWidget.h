// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "UObject/Object.h"
#include "CodexListEntryWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class ANYTHINGTODECLARE_API UCodexListEntryWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	UFUNCTION()
	TArray<UCodexListEntryWidget*> GetItemChildren() { return Children; };

	UFUNCTION()
	void SetLinkedData(const UDataAsset* InData);
	
	UPROPERTY()
	const UDataAsset* LinkedData;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* EntryTitle;

	TArray<UCodexListEntryWidget*> Children;
};
