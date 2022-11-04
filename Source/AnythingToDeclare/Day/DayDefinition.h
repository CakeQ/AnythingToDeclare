#pragma once

#include "CoreMinimal.h"

#include "../Character/CharacterModifier.h"

#include <Engine/DataAsset.h>

#include "DayDefinition.generated.h"

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
	TMap<ECharacterModifier, float> CharacterModifiers;

	UPROPERTY(EditDefaultsOnly)
	TArray<UCharacterAppearanceDataAsset*> CharacterAppearances;
};
