// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/QuestionContextGetterInterface.h"
#include "Interfaces/QuestionContextInterface.h"
#include "UObject/Object.h"
#include "CodexGenericViewWidget.generated.h"

class UQuestionHighlightBox;
class UImage;
class UTextBlock;

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class ANYTHINGTODECLARE_API UCodexGenericViewWidget : public UUserWidget, public IQuestionContextGetterInterface
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void SetCodexEntry(const UObject* InObject);
	virtual void GetQuestionContextData(TArray<UObject*>& OutArray) const override;

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* EntryName;
	
	UPROPERTY(meta = (BindWidget))
	UQuestionHighlightBox* EntryNameHighlightBox;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* EntryDescription;
	
	UPROPERTY(meta = (BindWidget))
	UImage* EntryIcon;
};
