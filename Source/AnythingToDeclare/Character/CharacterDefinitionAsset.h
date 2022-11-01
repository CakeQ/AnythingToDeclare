#pragma once

#include "CoreMinimal.h"

#include <Engine/DataAsset.h>

#include "CharacterDefinitionAsset.generated.h"

UCLASS(Blueprintable)
class UCharacterDefinitionAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	int32 Age;
	
	UPROPERTY(EditDefaultsOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly)
	FString CallSign;
	
	UPROPERTY(EditDefaultsOnly)
	FSoftObjectPath Portrait;
	
	UPROPERTY(EditDefaultsOnly)
	FSoftObjectPath FacePortrait;
};
