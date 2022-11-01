#pragma once

#include "CoreMinimal.h"

#include "../Character/CharacterModifier.h"

#include <Engine/DataAsset.h>

#include "DayDefinition.generated.h"

class UCharacterAppearanceDataAsset;

UCLASS(Blueprintable)
class UDayDefinitionAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	int32 DayNumber;

	UPROPERTY(EditDefaultsOnly)
	TMap<ECharacterModifier, float> CharacterModifiers;

	UPROPERTY(EditDefaultsOnly)
	TArray<UCharacterAppearanceDataAsset*> CharacterAppearances;
};
