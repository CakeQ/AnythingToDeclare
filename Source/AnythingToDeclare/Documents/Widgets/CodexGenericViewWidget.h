// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UObject/Object.h"
#include "CodexGenericViewWidget.generated.h"

class UImage;
class UTextBlock;

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class ANYTHINGTODECLARE_API UCodexGenericViewWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SetCodexEntry(const UObject* InObject) const;
	
private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* EntryName;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* EntryDescription;
	
	UPROPERTY(meta = (BindWidget))
	UImage* EntryIcon;
};
