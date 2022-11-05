// Copyright Daniel Thompson and Archie Whitehead


#include "HoldToConfirmButton.h"

UHoldToConfirmButton::UHoldToConfirmButton(const FObjectInitializer& InInitialiser)
	: Super(InInitialiser)
	, HasConfirmed(false)
	, ConfirmTime(2.0f)
	, ProgressedTime(0.0f)
{
}

void UHoldToConfirmButton::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if(ButtonWidget != nullptr)
	{
		if(ButtonWidget->IsPressed())
		{
			ProgressedTime += InDeltaTime;
			if(ProgressBar != nullptr)
			{
				ProgressBar->SetPercent(FMath::Min(ProgressedTime / ConfirmTime, 1.0f));
			}
			
			if(ProgressedTime >= ConfirmTime)
			{
				FireOnConfirmed();
			}
		}
		else if(!FMath::IsNearlyZero(ProgressedTime))
		{
			CancelConfirm();
		}
	}
}

void UHoldToConfirmButton::CancelConfirm()
{
	HasConfirmed = false;
	ProgressedTime = 0.0f;
	if(ProgressBar != nullptr)
	{
		ProgressBar->SetPercent(ProgressedTime / ConfirmTime);
	}
}

void UHoldToConfirmButton::FireOnConfirmed()
{
	OnConfirmed.Broadcast();
	HasConfirmed = true;
}
