// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "Components/CheckBox.h"
#include "Interfaces/QuestionContextInterface.h"
#include "UObject/Object.h"
#include "QuestionHighlightBox.generated.h"

class UTextBlock;
class UCheckBox;
class UQuestionHighlightBox;

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnHighlightChangedDelegate, const bool, IsHighlighted, UQuestionHighlightBox*, SourceWidget);

/**
 * 
 */
UCLASS(Blueprintable)
class ANYTHINGTODECLARE_API UQuestionHighlightBox final : public UCheckBox, public IQuestionContextInterface
{
	GENERATED_BODY()
	
public:
	virtual void GetQuestionContextData(FDialogueQuestion& InQuestion) const override;
	virtual void SetRequestTags(const TArray<FGameplayTag>& InTags) override;
	virtual void BindQuestionHighlighting(UObject* InObject, const FName& InFunctionName) override;

	UFUNCTION()
	void OnCheckBoxStateChanged(bool bBIsChecked);
	
	void SetLinkedData(const UObject* InDataAsset);
	void SetHighlightableState(const TArray<FGameplayTag>& InRequestTags);
public:
	FOnHighlightChangedDelegate OnHighlightChanged;
	
private:
	UPROPERTY(EditAnywhere, Category = "Context")
	FGameplayTag ContextTag;

	UPROPERTY(EditAnywhere, Category = "Context")
	TArray<FGameplayTag> RequestTagsThatAllowHighlighting;
	
	UPROPERTY()
	const UObject* LinkedDataAsset;
	
protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
};
