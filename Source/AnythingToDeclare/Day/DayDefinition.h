#pragma once

#include "CoreMinimal.h"

#include "AnythingToDeclare/Request/CustomsRequestModifier.h"

#include <Engine/DataAsset.h>

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
	TMap<ECustomsRequestModifier, float> CharacterModifiers;

	UPROPERTY(EditDefaultsOnly)
	TMap<int32, float> CargoManifestComplexityWeights;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<UCharacterAppearanceDataAsset*> CharacterAppearances;
};
