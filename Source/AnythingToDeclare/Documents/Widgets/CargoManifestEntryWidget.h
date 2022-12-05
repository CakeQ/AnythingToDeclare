#pragma once

#include "CoreMinimal.h"
#include "AnythingToDeclare/Documents/CargoManifest.h"
#include "Interfaces/QuestionContextGetterInterface.h"
#include "Interfaces/QuestionContextInterface.h"

#include "UMG/Public/Blueprint/UserWidget.h"

#include "CargoManifestEntryWidget.generated.h"

class UQuestionHighlightBox;
class UTextBlock;

UCLASS(Abstract, Blueprintable)
class UCargoManifestEntryWidget : public UUserWidget, public IQuestionContextGetterInterface
{
	GENERATED_BODY()
public:
	virtual void SetCargoManifestEntry(const FCargoManifestEntry& InManifestEntry);
	virtual void GetQuestionContextData(TArray<UObject*>& OutArray) const override;

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CargoTypeName;
	
	UPROPERTY(meta = (BindWidget))
	UQuestionHighlightBox* CargoTypeNameHighlightBox;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CargoUnits;
	
	UPROPERTY(meta = (BindWidget))
	UQuestionHighlightBox* CargoUnitsHighlightBox;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CargoWeight;
	
	UPROPERTY(meta = (BindWidget))
	UQuestionHighlightBox* CargoWeightHighlightBox;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CargoValue;
	
	UPROPERTY(meta = (BindWidget))
	UQuestionHighlightBox* CargoValueHighlightBox;
};
