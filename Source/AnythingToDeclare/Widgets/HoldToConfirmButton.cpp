// Copyright Daniel Thompson and Archie Whitehead


#include "HoldToConfirmButton.h"

UHoldToConfirmButton::UHoldToConfirmButton()
	: ConfirmTime(2.0f)
{
}

void UHoldToConfirmButton::PostLoad()
{
	Super::PostLoad();

	OnPressed.AddDynamic(this, &UHoldToConfirmButton::StartConfirm);
	OnReleased.AddDynamic(this, &UHoldToConfirmButton::CancelConfirm);
}

void UHoldToConfirmButton::StartConfirm()
{
	if(!ConfirmTimer.IsValid())
	{
		if(const UWorld* World = GetWorld())
		{
			FTimerManager& TimerManager = World->GetTimerManager();
			TimerManager.SetTimer(ConfirmTimer, this, &UHoldToConfirmButton::OnConfirmed, ConfirmTime, false);
		}
	}
}

void UHoldToConfirmButton::CancelConfirm()
{
	if(const UWorld* World = GetWorld())
	{
		FTimerManager& TimerManager = World->GetTimerManager();
		TimerManager.ClearTimer(ConfirmTimer);
	}
}

void UHoldToConfirmButton::OnConfirmed()
{
	OnConfirmedEvent.Broadcast();
	ConfirmTimer.Invalidate();
}
