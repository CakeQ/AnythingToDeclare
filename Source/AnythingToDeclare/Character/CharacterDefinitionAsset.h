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
	int32 CryogenicAge;
	
	UPROPERTY(EditDefaultsOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly)
	FString Surname;
	
	UPROPERTY(EditDefaultsOnly)
	FString CallSign;

	UPROPERTY(EditDefaultsOnly)
	FString ShipName;
	
	UPROPERTY(EditDefaultsOnly, meta=(MetaClass="/Script/Engine.Texture"))
	FSoftObjectPath Portrait;
	
	UPROPERTY(EditDefaultsOnly, meta=(MetaClass="/Script/Engine.Texture"))
	FSoftObjectPath FacePortrait;
};
