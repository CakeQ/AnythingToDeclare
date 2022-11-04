// Copyright Daniel Thompson and Archie Whitehead

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "UObject/Object.h"
#include "HoldToConfirmButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonConfirmedEvent);

/**
 * 
 */
UCLASS()
class ANYTHINGTODECLARE_API UHoldToConfirmButton : public UButton
{
	GENERATED_BODY()

public:
	UHoldToConfirmButton();
	
	virtual void PostLoad() override;

	void StartConfirm();
	void CancelConfirm();
	void OnConfirmed();
	
private:
	UPROPERTY(EditAnywhere)
	float ConfirmTime;
	
	FTimerHandle ConfirmTimer;

	FOnButtonConfirmedEvent OnConfirmedEvent;
};
