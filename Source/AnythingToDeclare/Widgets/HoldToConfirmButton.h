// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "UObject/Object.h"
#include "HoldToConfirmButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonConfirmedEvent);

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class ANYTHINGTODECLARE_API UHoldToConfirmButton : public UUserWidget
{
	GENERATED_BODY()

public:
	UHoldToConfirmButton(const FObjectInitializer& InInitialiser);
	
	void CancelConfirm();
	void FireOnConfirmed();

	FOnButtonConfirmedEvent OnConfirmed;
	
protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
private:
	UPROPERTY(EditDefaultsOnly)
	bool ResetOnConfirm;
	
	bool HasConfirmed;
	
	UPROPERTY(EditAnywhere)
	float ConfirmTime;

	float ProgressedTime;
	
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonWidget;
	
	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	UProgressBar* ProgressBar;
};
