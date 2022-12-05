#pragma once

#include "CoreMinimal.h"
#include "AnythingToDeclare/Widgets/CustomsRequestCodexMonitorWidget.h"
#include "Components/ScrollBox.h"
#include "Interfaces/QuestionContextInterface.h"

#include "UMG/Public/Blueprint/UserWidget.h"

#include "CodexWidget.generated.h"

class UWidgetSwitcher;
class UCodexListEntry;
class UTreeView;

UCLASS(Abstract, Blueprintable)
class UCodexWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void SetCodexList(const TArray<UCodexListEntry*>& InList) const;

	UFUNCTION()
	void OnGetChildren(UObject* Entry, TArray<UObject*>& OutChildren);
	
	UFUNCTION()
	void UpdateListEntryExpansion(UObject* Entry, const bool bIsExpanded);
	
	UFUNCTION()
	void SetActiveEntry(UObject* Entry);

	UFUNCTION()
	void UnselectEntryAndChildren(UObject* Entry, const UObject* IgnoreObject);

	bool GetEntryLayer(UObject* Entry, int32& LayerCount, const TArray<UObject*>& Entries);
	bool TryToFindAndShowData(const UObject* InData);

	UObject* FindLinkedDataIterative(UObject* Parent, const UObject* LinkedData);

	UPROPERTY(meta = (BindWidget))
	UTreeView* CodexList;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* CodexViewSwitcher;
	
protected:
	UPROPERTY()
	TArray<UCodexListEntry*> BaseCodexListItems;
};
