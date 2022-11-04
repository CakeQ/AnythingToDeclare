// Copyright Epic Games, Inc. All Rights Reserved.

#include "AnythingToDeclareGameMode.h"

#include "AnythingToDeclareDeveloperSettings.h"
#include "AnythingToDeclarePlayerController.h"
#include "AnythingToDeclarePawn.h"

#include "Day/DayDefinitionMap.h"
#include "Loader.h"

AAnythingToDeclareGameMode::AAnythingToDeclareGameMode(const FObjectInitializer& InInitializer)
	: Super(InInitializer)
	, DayNumber(1)
	, CurrentCharacterCount(1)
{
	DefaultPawnClass = AAnythingToDeclarePawn::StaticClass();
	PlayerControllerClass = AAnythingToDeclarePlayerController::StaticClass();
}

void AAnythingToDeclareGameMode::BeginPlay()
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
}

void AAnythingToDeclareGameMode::StartDay(const int32 InDayNumber)
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

void AAnythingToDeclareGameMode::OnDayLoaded(const UDayDefinitionAsset* InDayAsset)
{
	CurrentDayDefinition = InDayAsset;
}

void AAnythingToDeclareGameMode::OnDayNotFound()
{
}
