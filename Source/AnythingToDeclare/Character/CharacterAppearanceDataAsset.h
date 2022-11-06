#pragma once

#include "CoreMinimal.h"

#include "../Request/CustomsRequestModifier.h"
#include "GameplayTagContainer.h"

#include <Engine/DataAsset.h>

#include "CharacterAppearanceDataAsset.generated.h"

enum class ECustomsRequestType : uint8;
class UCharacterDefinitionAsset;
class USubLocationDefinition;

UCLASS(Blueprintable)
class UCharacterAppearanceDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	int32 CharacterPosition;

	UPROPERTY(EditDefaultsOnly)
	ECustomsRequestType CustomsRequestType;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<ECustomsRequestModifier, float> CharacterModifiers;

	// UPROPERTY()
	// TArray<FDialogueData> DialogueOptions;
	
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag TagOnApprove;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag TagOnDenied;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<FGameplayTag> TagRequirements;
	
	UPROPERTY(EditDefaultsOnly)
	UCharacterDefinitionAsset* Character;

	UPROPERTY(EditDefaultsOnly)
	USubLocationDefinition* OriginLocation;

	UPROPERTY(EditDefaultsOnly)
	USubLocationDefinition* DestinationLocation;
};
