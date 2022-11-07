// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#pragma once

#include "CoreMinimal.h"
#include "HoldToConfirmButton.h"
#include "Components/Button.h"
#include "UObject/Object.h"
#include "CustomsActionsBar.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class ANYTHINGTODECLARE_API UCustomsActionsBar : public UUserWidget
{
	GENERATED_BODY()

public:
	UCustomsActionsBar(const FObjectInitializer& ObjectInitializer);

private:
	UPROPERTY(meta = (BindWidget))
	UHoldToConfirmButton* AllowButton;
	
	UPROPERTY(meta = (BindWidget))
	UHoldToConfirmButton* DenyButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* QuestionButton;
};
