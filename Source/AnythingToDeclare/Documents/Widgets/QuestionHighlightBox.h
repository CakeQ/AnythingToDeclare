// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "Components/CheckBox.h"
#include "Interfaces/QuestionContextInterface.h"
#include "UObject/Object.h"
#include "QuestionHighlightBox.generated.h"

enum class EGameplayTagModifier : uint8;
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
	virtual void BindQuestionHighlighting(UObject* InObject, const FName& InFunctionName) override;

	UFUNCTION()
	void OnCheckBoxStateChanged(bool bBIsChecked);

	const UObject* GetLinkedData() const;
	void SetLinkedData(const UObject* InData);
	void SetLinkedData(const UObject* InData, const TArray<FGameplayTag>& InTags);
	
	FOnHighlightChangedDelegate OnHighlightChanged;
	
private:
	UPROPERTY(EditAnywhere, Category = "Context")
	FGameplayTag ContextTag;

	UPROPERTY()
	const UObject* LinkedData;
	
	UPROPERTY()
	TArray<FGameplayTag> LinkedTags;
	
protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
};
