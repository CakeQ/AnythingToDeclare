// Copyright Daniel Thompson @https://github.com/cakeq. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "AnythingToDeclareDeveloperSettings.generated.h"

/**
 * 
 */
UCLASS(config=Game, defaultconfig, meta=(DisplayName="AnythingToDeclare"))
class ANYTHINGTODECLARE_API UAnythingToDeclareDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, config)
	FSoftObjectPath DayDefinitionDataMap;

	static UAnythingToDeclareDeveloperSettings* Get() { return GetMutableDefault<UAnythingToDeclareDeveloperSettings>(); }
};
