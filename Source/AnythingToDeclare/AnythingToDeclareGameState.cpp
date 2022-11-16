﻿// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#include "AnythingToDeclareGameState.h"

#include "AnythingToDeclareDeveloperSettings.h"
#include "Day/DayDefinitionMap.h"
#include "Request/CustomsRequestDataMap.h"
#include "Loader.h"
#include "Camera/CameraActor.h"
#include "Documents/Widgets/CodexWidget.h"
#include "Documents/Widgets/CodexWidgetHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Request/CustomsRequestGenerator.h"
#include "Widgets/CustomsRequestMonitorWidget.h"

AAnythingToDeclareGameState::AAnythingToDeclareGameState(const FObjectInitializer& InInitializer)
	: Super(InInitializer)
	, DayNumber(1)
	, CurrentRequestCount(0)
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
			if(CustomsDataMap != nullptr)
			{
				StartDay(1);
			}
	   });
	}

	if(const UAnythingToDeclareDeveloperSettings* DeveloperSettings = UAnythingToDeclareDeveloperSettings::Get())
	{
		FLoader::Load<UCustomsRequestDataMap>(DeveloperSettings->CustomsDataMap, [this](UCustomsRequestDataMap& InLoadedDataMap)
	   {
			CustomsDataMap = &InLoadedDataMap;
			if(DayDataMap != nullptr)
			{
				StartDay(1);
			}
			if(UCodexWidget* CodexWidget = CachedCodexWidget.Get())
			{
				CodexWidgetHelper::GenerateCodexListFromRegions(CodexWidget, InLoadedDataMap.SubLocations);
			}
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
			
			if(const UWidgetComponent* WidgetComponent = ConsolePtr->GetScreenWidget())
			{
				if(UCustomsRequestMonitorWidget* RequestMonitorWidget = Cast<UCustomsRequestMonitorWidget>(WidgetComponent->GetWidget()))
				{
					CachedRequestMonitorWidget = RequestMonitorWidget;
					if(const UCustomsActionsBar* ActionBar = RequestMonitorWidget->ActionBar)
					{
						if(ActionBar->AllowButton != nullptr)
						{
							ActionBar->AllowButton->OnConfirmed.AddDynamic(this, &AAnythingToDeclareGameState::OnRequestApproved);
						}
						if(ActionBar->DenyButton != nullptr)
						{
							ActionBar->DenyButton->OnConfirmed.AddDynamic(this, &AAnythingToDeclareGameState::OnRequestDenied);
						}
						if(ActionBar->QuestionButton != nullptr)
						{
							ActionBar->QuestionButton->OnReleased.AddDynamic(this, &AAnythingToDeclareGameState::OnQuestioned);
						}
					}
				}
				
				if(UCodexWidget* CodexWidget = Cast<UCodexWidget>(WidgetComponent->GetWidget()))
				{
					CachedCodexWidget = CodexWidget;
				}
			}
		}
	}
}

void AAnythingToDeclareGameState::StartDay(const int32 InDayNumber)
{
	DayNumber = InDayNumber;
	CurrentRequestCount = 1;
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
	NextRequest();
}

void AAnythingToDeclareGameState::OnDayNotFound()
{
}

void AAnythingToDeclareGameState::NextRequest()
{
	CurrentRequestCount++;
	CurrentRequest = FCustomsRequest();
	for(UCharacterAppearanceDataAsset* Appearance : CurrentDayDefinition->CharacterAppearances)
	{
		if(Appearance->CharacterPosition == CurrentRequestCount)
		{
			CurrentRequest.CharacterAppearance = Appearance;
		}
	}

	CustomsRequestsHelper::GenerateRequest(CurrentRequest, CustomsDataMap, CurrentDayDefinition);
	if(const UCustomsRequestMonitorWidget* RequestMonitorWidget = CachedRequestMonitorWidget.Get())
	{
		if(RequestMonitorWidget->ManifestWidget != nullptr)
		{
			RequestMonitorWidget->ManifestWidget->SetCargoManifest(CurrentRequest.CargoManifest);
		}
	}
}

void AAnythingToDeclareGameState::OnRequestApproved()
{
	HandleRequest(ECustomsRequestOutcome::Approved);
}

void AAnythingToDeclareGameState::OnRequestDenied()
{
	HandleRequest(ECustomsRequestOutcome::Denied);
}

void AAnythingToDeclareGameState::OnQuestioned()
{
}

void AAnythingToDeclareGameState::HandleRequest(const ECustomsRequestOutcome& InOutcome)
{
	if(CurrentRequest.IsValid())
	{
		CurrentRequest.Outcome = InOutcome;
		ProcessedRequests.Add(CurrentRequest);
	}
	NextRequest();
}

AActor* AAnythingToDeclareGameState::CycleCameraNext()
{
	int32 CurrentCameraOrder = 0;
	AGenericConsole* ConsoleToReturn = nullptr;
	
	if(const AGenericConsole* FocusedConsolePtr = FocusedConsole.Get())
	{
		CurrentCameraOrder = FocusedConsolePtr->GetCameraOrder();
	}

	for(const TWeakObjectPtr<AGenericConsole>& Console : Consoles)
	{
		if(AGenericConsole* ConsolePtr = Console.Get())
		{
			if(CurrentCameraOrder < ConsolePtr->GetCameraOrder() && (ConsoleToReturn == nullptr
				 || ConsolePtr->GetCameraOrder() < ConsoleToReturn->GetCameraOrder()))
			{
				ConsoleToReturn = ConsolePtr;
			}
		}
	}
	if(ConsoleToReturn != nullptr && ConsoleToReturn != FocusedConsole)
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
	return nullptr;
}

AActor* AAnythingToDeclareGameState::CycleCameraPrev()
{
	int32 CurrentCameraOrder = 200;
	AGenericConsole* ConsoleToReturn = nullptr;
	
	if(const AGenericConsole* FocusedConsolePtr = FocusedConsole.Get())
	{
		CurrentCameraOrder = FocusedConsolePtr->GetCameraOrder();
	}

	for(const TWeakObjectPtr<AGenericConsole>& Console : Consoles)
	{
		if(AGenericConsole* ConsolePtr = Console.Get())
		{
			if(CurrentCameraOrder > ConsolePtr->GetCameraOrder() && (ConsoleToReturn == nullptr
				 || ConsolePtr->GetCameraOrder() > ConsoleToReturn->GetCameraOrder()))
			{
				ConsoleToReturn = ConsolePtr;
			}
		}
	}
	if(ConsoleToReturn != nullptr && ConsoleToReturn != FocusedConsole)
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
	return nullptr;
}

