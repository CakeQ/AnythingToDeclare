#pragma once

#include "CoreMinimal.h"

#include "../Request/CustomsRequestModifier.h"
#include "GameplayTagContainer.h"

#include <Engine/DataAsset.h>

#include "CharacterAppearanceDataAsset.generated.h"

class UDataTable;
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
	
	UPROPERTY(EditDefaultsOnly, meta = (ToolTip = "Percentage based modifier chances. 1.0 for 100%"))
	TMap<FGameplayTag, float> CharacterModifiers;

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
	
	UPROPERTY(EditDefaultsOnly)
	UDataTable* Dialogue;
};
