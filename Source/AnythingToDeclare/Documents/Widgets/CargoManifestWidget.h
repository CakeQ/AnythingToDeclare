#pragma once

#include "CoreMinimal.h"
#include "AnythingToDeclare/Documents/CargoManifest.h"

#include "UMG/Public/Blueprint/UserWidget.h"
#include "UMG/Public/Components/Verticalbox.h"

#include "CargoManifestWidget.generated.h"

class UCargoManifestEntryWidget;
class UTextBlock;

UCLASS(Abstract, Blueprintable)
class UCargoManifestWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	virtual void SetCargoManifest(const FCargoManifest& InManifest);
	
protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ShipName;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* OriginPlanet;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DestinationPlanet;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* CargoManifestEntries;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCargoManifestEntryWidget> CargoManifestEntryWidgetClass;
};
