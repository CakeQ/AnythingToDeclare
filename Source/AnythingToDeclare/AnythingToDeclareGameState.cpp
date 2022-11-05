// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/


#include "AnythingToDeclareGameState.h"

#include "AnythingToDeclareDeveloperSettings.h"
#include "Day/DayDefinitionMap.h"
#include "Loader.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"

AAnythingToDeclareGameState::AAnythingToDeclareGameState(const FObjectInitializer& InInitializer)
	: Super(InInitializer)
	, DayNumber(1)
	, CurrentCharacterCount(1)
{
}

void AAnythingToDeclareGameState::BeginPlay()
{
	Super::BeginPlay();

	if(const UAnythingToDeclareDeveloperSettings* DeveloperSettings = UAnythingToDeclareDeveloperSettings::Get())
	{
		FLoader::Load<UDayDefinitionMap>(DeveloperSettings->DayDefinitionDataMap, [this](UDayDefinitionMap& InLoadedDataMap)
	   {
			DayDataMap = &InLoadedDataMap;
			StartDay(1);
	   });
	}

	TArray<AActor*> WorldConsoles;	
	UGameplayStatics::GetAllActorsOfClass(this, AGenericConsole::StaticClass(), WorldConsoles);
	for(AActor* Console : WorldConsoles)
	{
		if(AGenericConsole* ConsolePtr = static_cast<AGenericConsole*>(Console))
		{
			MaxCameraOrder = ConsolePtr->GetCameraOrder() > MaxCameraOrder ? ConsolePtr->GetCameraOrder() : MaxCameraOrder;
			Consoles.Add(ConsolePtr);
		}
	}
	
}

void AAnythingToDeclareGameState::StartDay(const int32 InDayNumber)
{
	DayNumber = InDayNumber;
	CurrentCharacterCount = 1;
	if(DayDataMap != nullptr)
	{
		if(const UDayDefinitionAsset* DayDefinitionAsset = DayDataMap->FindDayNumber(InDayNumber))
		{
			OnDayLoaded(DayDefinitionAsset);
		}
		else
		{
			OnDayNotFound();
		}
	}
	else
	{
		OnDayNotFound();
	}
}

void AAnythingToDeclareGameState::OnDayLoaded(const UDayDefinitionAsset* InDayAsset)
{
	CurrentDayDefinition = InDayAsset;
}

void AAnythingToDeclareGameState::OnDayNotFound()
{
}

void AAnythingToDeclareGameState::SetPrimaryCameraActor(AActor* InActor)
{
	PrimaryCameraActor = InActor;
}

AActor* AAnythingToDeclareGameState::CycleCameraNext()
{
	int32 CurrentCameraOrder = 0;
	if(const AGenericConsole* FocusedConsolePtr = FocusedConsole.Get())
	{
		CurrentCameraOrder = FocusedConsolePtr->GetCameraOrder();
	}

	AGenericConsole* ConsoleToReturn = nullptr;
	for(const TWeakObjectPtr<AGenericConsole>& Console : Consoles)
	{
		if(AGenericConsole* ConsolePtr = Console.Get())
		{
			if(ConsoleToReturn == nullptr || (ConsolePtr->GetCameraOrder() > CurrentCameraOrder && ConsoleToReturn->GetCameraOrder() < ConsolePtr->GetCameraOrder()))
			{
				ConsoleToReturn = ConsolePtr;
			}
		}
	}
	if(ConsoleToReturn != nullptr)
	{
		FocusedConsole = ConsoleToReturn;
		// ConsolePtr->Focus();
		return ConsoleToReturn;
	}

	if(FocusedConsole.IsValid())
	{
		if(const AGenericConsole* FocusedConsolePtr = FocusedConsole.Get())
		{
			// FocusedConsolePtr->UnFocus();
		}
		FocusedConsole = nullptr;
	}
	return PrimaryCameraActor;
}

AActor* AAnythingToDeclareGameState::CycleCameraPrev()
{
	int32 CurrentCameraOrder = 0;
	if(const AGenericConsole* FocusedConsolePtr = FocusedConsole.Get())
	{
		CurrentCameraOrder = FocusedConsolePtr->GetCameraOrder();
	}

	AGenericConsole* ConsoleToReturn = nullptr;
	for(const TWeakObjectPtr<AGenericConsole>& Console : Consoles)
	{
		if(AGenericConsole* ConsolePtr = Console.Get())
		{
			if(ConsoleToReturn == nullptr || (ConsolePtr->GetCameraOrder() < CurrentCameraOrder && ConsoleToReturn->GetCameraOrder() > ConsolePtr->GetCameraOrder()))
			{
				ConsoleToReturn = ConsolePtr;
				break;
			}
		}
	}
	if(ConsoleToReturn != nullptr)
	{
		FocusedConsole = ConsoleToReturn;
		// ConsolePtr->Focus();
		return ConsoleToReturn;
	}

	if(FocusedConsole.IsValid())
	{
		if(const AGenericConsole* FocusedConsolePtr = FocusedConsole.Get())
		{
			// FocusedConsolePtr->UnFocus();
		}
		FocusedConsole = nullptr;
	}
	return PrimaryCameraActor;
}

