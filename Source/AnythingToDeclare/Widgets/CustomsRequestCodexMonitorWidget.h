﻿// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#pragma once

#include "CoreMinimal.h"
#include "AnythingToDeclare/Documents/Widgets/Interfaces/QuestionContextInterface.h"

#include "Blueprint/UserWidget.h"

#include "CustomsRequestCodexMonitorWidget.generated.h"

class UWidgetSwitcher;
class UCodexWidget;

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class ANYTHINGTODECLARE_API UCustomsRequestCodexMonitorWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UCustomsRequestCodexMonitorWidget(const FObjectInitializer& ObjectInitializer);
	
	void TryToFindAndShowData(const UObject* InData) const;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UWidgetSwitcher* CodexSwitcher;
	
	UPROPERTY(meta = (BindWidget))
	UCodexWidget* CargoCodex;
	
	UPROPERTY(meta = (BindWidget))
	UCodexWidget* LocationCodex;
};
