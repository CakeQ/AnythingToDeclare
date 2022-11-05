// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#pragma once

#include "CoreMinimal.h"

#include "Console/GenericConsole.h"
#include "Day/DayDefinition.h"
#include "Documents/Widgets/CargoManifestWidget.h"
#include "GameFramework/GameStateBase.h"

#include "AnythingToDeclareGameState.generated.h"

class UDayDefinitionMap;
class UDayDefinitionAsset;

UCLASS()
class ANYTHINGTODECLARE_API AAnythingToDeclareGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AAnythingToDeclareGameState(const FObjectInitializer& InInitializer);

	virtual void BeginPlay() override;
	
	void StartDay(const int32 InDayNumber);

	UFUNCTION()
	void OnDayLoaded(const UDayDefinitionAsset* InDayAsset);

	UFUNCTION()
	void OnDayNotFound();

	void SetPrimaryCameraActor(AActor* InActor);
	
	UFUNCTION()
	AActor* CycleCameraNext();
	
	UFUNCTION()
	AActor* CycleCameraPrev();
	
private:
	UPROPERTY(VisibleAnywhere)
	int32 DayNumber;

	UPROPERTY(VisibleAnywhere)
	int32 CurrentCharacterCount;

	int32 MaxCameraOrder;
	
	UPROPERTY(VisibleAnywhere)
	const UDayDefinitionAsset* CurrentDayDefinition;
	
	UPROPERTY()
	UDayDefinitionMap* DayDataMap;

	UPROPERTY()
	TWeakObjectPtr<UCargoManifestWidget> CargoManifestWidget;

	UPROPERTY()
	AActor* PrimaryCameraActor;

	UPROPERTY()
	TWeakObjectPtr<AGenericConsole> FocusedConsole;
	
	UPROPERTY()
	TArray<TWeakObjectPtr<AGenericConsole>> Consoles;
};
