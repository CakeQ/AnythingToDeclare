// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameModeBase.h"
#include "Day/DayDefinition.h"
#include "Documents/Widgets/CargoManifestWidget.h"

#include "AnythingToDeclareGameMode.generated.h"

class UDayDefinitionMap;
class UDayDefinitionAsset;

UCLASS()
class ANYTHINGTODECLARE_API AAnythingToDeclareGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAnythingToDeclareGameMode(const FObjectInitializer& InInitializer);

	virtual void BeginPlay() override;
	
	void StartDay(const int32 InDayNumber);

	UFUNCTION()
	void OnDayLoaded(const UDayDefinitionAsset* InDayAsset);

	UFUNCTION()
	void OnDayNotFound();
	
private:
	UPROPERTY(VisibleAnywhere)
	int32 DayNumber;

	UPROPERTY(VisibleAnywhere)
	int32 CurrentCharacterCount;
	
	UPROPERTY(VisibleAnywhere)
	const UDayDefinitionAsset* CurrentDayDefinition;
	
	UPROPERTY()
	UDayDefinitionMap* DayDataMap;

	UPROPERTY()
	TWeakObjectPtr<UCargoManifestWidget> CargoManifestWidget;
};



