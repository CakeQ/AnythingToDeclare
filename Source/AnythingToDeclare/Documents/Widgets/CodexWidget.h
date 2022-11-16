#pragma once

#include "CoreMinimal.h"
#include "Components/ScrollBox.h"

#include "UMG/Public/Blueprint/UserWidget.h"

#include "CodexWidget.generated.h"

class UCodexListEntryWidget;
class UTreeView;
class UTextBlock;

UCLASS(Abstract, Blueprintable)
class UCodexWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	// UFUNCTION(BlueprintCallable)
	// virtual void SetCargoManifest(const FCargoManifest& InManifest);
	//

	virtual void PostInitProperties() override;
	
	void SetCodexList(const TArray<UCodexListEntryWidget*> InList) const;

	UFUNCTION()
	void OnGetChildren(UObject* Entry, TArray<UObject*>& OutChildren);
	
	UPROPERTY(meta = (BindWidget))
	UTreeView* CodexList;

protected:
	
	// UPROPERTY(meta = (BindWidget))
	// UGenericCodexTabWidget* Locations;
	//
	// UPROPERTY(meta = (BindWidget))
	// UGenericCodexTabWidget* Cargo;
	//
	// UPROPERTY(meta = (BindWidget))
	// UGenericCodexTabWidget* Cargo;
	//
	// UPROPERTY(meta = (BindWidget))
	// UTextBlock* OriginPlanet;
	//
	// UPROPERTY(meta = (BindWidget))
	// UTextBlock* OriginSubLocation;
	//
	// UPROPERTY(meta = (BindWidget))
	// UTextBlock* DestinationPlanet;
	//
	// UPROPERTY(meta = (BindWidget))
	// UTextBlock* DestinationSubLocation;
	//
	// UPROPERTY(meta = (BindWidget))
	// UScrollBox* CargoManifestEntries;
	//
	// UPROPERTY(EditDefaultsOnly)
	// TSubclassOf<UCargoManifestEntryWidget> CargoManifestEntryWidgetClass;

	UPROPERTY()
	TArray<UCodexListEntryWidget*> BaseCodexListItems;
};
