#pragma once

#include "CoreMinimal.h"
#include "AnythingToDeclare/Documents/CargoManifest.h"
#include "Interfaces/QuestionContextGetterInterface.h"

#include "UMG/Public/Blueprint/UserWidget.h"

#include "CargoManifestWidget.generated.h"

class UScrollBox;
class UQuestionHighlightBox;
class UQuestionHighlightWidget;
class UCargoManifestEntryWidget;
class UTextBlock;

UCLASS(Abstract, Blueprintable)
class UCargoManifestWidget : public UUserWidget, public IQuestionContextGetterInterface
{
	GENERATED_BODY()
public:
	virtual void SetCargoManifest(const FCargoManifest& InManifest);
	virtual void GetQuestionContextData(TArray<UObject*>& OutArray) const override;

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ShipName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* OriginPlanet;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* OriginSubLocation;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DestinationPlanet;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DestinationSubLocation;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* CargoManifestEntries;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CargoWeightTotal;
	
	UPROPERTY(meta = (BindWidget))
	UQuestionHighlightBox* OriginPlanetHighlightBox;
	
	UPROPERTY(meta = (BindWidget))
	UQuestionHighlightBox* OriginSubLocationHighlightBox;
	
	UPROPERTY(meta = (BindWidget))
	UQuestionHighlightBox* DestinationPlanetHighlightBox;
	
	UPROPERTY(meta = (BindWidget))
	UQuestionHighlightBox* DestinationSubLocationHighlightBox;
	
	UPROPERTY(meta = (BindWidget))
	UQuestionHighlightBox* CargoWeightTotalHighlightBox;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCargoManifestEntryWidget> CargoManifestEntryWidgetClass;
};
