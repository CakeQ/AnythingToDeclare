// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "UObject/Object.h"
#include "CodexListEntryWidget.generated.h"

class UCodexListEntry;
class UCheckBox;
class UCodexListEntryWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnExpansionUpdatedevent, UObject*, Item, bool, IsExpanded);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectedEvent, UObject*, Item);

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class ANYTHINGTODECLARE_API UCodexListEntryWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void NativeOnInitialized() override;
	
	UFUNCTION()
	void OnExpansionStateChanged(bool bBIsChecked);
	
	UFUNCTION()
	void OnSelectionStateChanged(bool bBIsChecked);
	
protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;

	UPROPERTY()
	UCodexListEntry* LinkedData;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* EntryTitle;

	UPROPERTY(meta = (BindWidget))
	UCheckBox* EntryExpansion;
	
	UPROPERTY(meta = (BindWidget))
	UCheckBox* EntrySelection;
	
	FOnExpansionUpdatedevent OnExpansionUpdated;

	FOnSelectedEvent OnSelectedEvent;
};
