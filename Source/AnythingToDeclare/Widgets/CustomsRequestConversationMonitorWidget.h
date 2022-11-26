// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UObject/Object.h"
#include "CustomsRequestConversationMonitorWidget.generated.h"

class UConversationWidget;

/**
 * 
 */
UCLASS()
class ANYTHINGTODECLARE_API UCustomsRequestConversationMonitorWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UCustomsRequestConversationMonitorWidget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(meta = (BindWidget))
	UConversationWidget* ConversationWidget;
};
