// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#pragma once

#include "CoreMinimal.h"
#include "AnythingToDeclare/Documents/Widgets/CodexGenericViewWidget.h"
#include "UObject/Object.h"
#include "CodexCargoViewWidget.generated.h"

class UButton;
class UTextBlock;
class UTextBox;

/**
 * 
 */
UCLASS()
class ANYTHINGTODECLARE_API UCodexCargoViewWidget : public UCodexGenericViewWidget
{
	GENERATED_BODY()

public:
	virtual void SetCodexEntry(const UObject* InObject) override;

	UFUNCTION()
	void AdjustUnitReference(int32 InAmount);
	
	UFUNCTION()
	void AddOneUnit();

	UFUNCTION()
	void AddTenUnits();

	UFUNCTION()
	void AddHundredUnits();

	UFUNCTION()
	void SubOneUnit();

	UFUNCTION()
	void SubTenUnits();

	UFUNCTION()
	void SubHundredUnits();
	
	UFUNCTION()
	void ResetUnits();
	
protected:
	virtual void NativeOnInitialized() override;
	void RefreshUnitDisplays();

private:
	UPROPERTY()
	int32 UnitReferenceValue;
	
	UPROPERTY(EditDefaultsOnly)
	int32 UnitReferenceValueMax;

	float ValuePerUnit;
	float WeightPerUnit;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* WeightPerUnitDisplay;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ValuePerUnitDisplay;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Category;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* IsIllegal;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* UnitReferenceValueView;

	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	UButton* UnitAddOneButton;

	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	UButton* UnitAddTenButton;

	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	UButton* UnitAddHundredButton;

	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	UButton* UnitSubOneButton;

	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	UButton* UnitSubTenButton;

	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	UButton* UnitSubHundredButton;

	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	UButton* UnitResetButton;
};
