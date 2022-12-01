﻿#pragma once

#include "CoreMinimal.h"

#include <Engine/DataAsset.h>

#include "GameplayTagContainer.h"
#include "AnythingToDeclare/Request/CustomsRequestType.h"
#include "DayDefinition.generated.h"

class USubLocationDefinition;
class UCharacterAppearanceDataAsset;

UCLASS(Blueprintable)
class ANYTHINGTODECLARE_API UDayDefinitionAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:

	const UCharacterAppearanceDataAsset* FindCharacterByAppearanceNumber(const int32 InNumber);
	
	UPROPERTY(EditDefaultsOnly)
	int32 DayNumber;
	
	UPROPERTY(EditDefaultsOnly)
	USubLocationDefinition* WorkLocationOverride;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<ECustomsRequestType, float> CustomsRequestTypeWeight;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<int32, float> CharacterModifierComplexityWeights;

	UPROPERTY(EditDefaultsOnly)
	TMap<int32, float> RequestModifierComplexityWeights;

	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag, float> CharacterModifierWeights;

	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag, float> RequestModifierWeights;

	UPROPERTY(EditDefaultsOnly)
	TMap<int32, float> CargoManifestComplexityWeights;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<UCharacterAppearanceDataAsset*> CharacterAppearances;
};
