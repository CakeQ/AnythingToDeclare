// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#pragma once

#include "CoreMinimal.h"

#include "CustomsActionsBar.h"
#include "AnythingToDeclare/Documents/Widgets/CargoManifestWidget.h"

#include "CustomsRequestMonitorWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class ANYTHINGTODECLARE_API UCustomsRequestMonitorWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UCustomsRequestMonitorWidget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(meta = (BindWidget))
	UCustomsActionsBar* ActionBar;
	
	UPROPERTY(meta = (BindWidget))
	UCargoManifestWidget* ManifestWidget;
};
