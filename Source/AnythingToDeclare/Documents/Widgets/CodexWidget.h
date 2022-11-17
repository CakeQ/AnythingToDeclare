#pragma once

#include "CoreMinimal.h"
#include "Components/ScrollBox.h"

#include "UMG/Public/Blueprint/UserWidget.h"

#include "CodexWidget.generated.h"

class UCodexGenericViewWidget;
class UCodexListEntry;
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

	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void SetCodexList(const TArray<UCodexListEntry*>& InList) const;

	UFUNCTION()
	void OnGetChildren(UObject* Entry, TArray<UObject*>& OutChildren);
	
	UFUNCTION()
	void UpdateListEntryExpansion(UObject* Entry, const bool bIsExpanded);
	
	UFUNCTION()
	void SetActiveEntry(UObject* Entry);

	UPROPERTY(meta = (BindWidget))
	UTreeView* CodexList;

	UPROPERTY(meta = (BindWidget))
	UCodexGenericViewWidget* CodexView;

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
	TArray<UCodexListEntry*> BaseCodexListItems;
};
