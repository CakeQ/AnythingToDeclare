#pragma once

#include "CoreMinimal.h"

#include "CharacterModifier.h"

#include <Engine/DataAsset.h>

#include "CharacterAppearanceDataAsset.generated.h"

class UCharacterDefinitionAsset;

UCLASS(Blueprintable)
class UCharacterAppearanceDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	int32 CharacterPosition;

	UPROPERTY(EditDefaultsOnly)
	TMap<ECharacterModifier, float> CharacterModifiers;

	// UPROPERTY()
	// TArray<FGameplayTag> GameplayTagRequirements;
	//
	// UPROPERTY()
	// TArray<FDialogueData> DialogueOptions;
	
	UPROPERTY(EditDefaultsOnly)
	UCharacterDefinitionAsset* Character;
};
