#pragma once

#include "CoreMinimal.h"

#include <Engine/DataAsset.h>

#include "CharacterDefinitionAsset.generated.h"

class UShipClassDefinition;
class UFactionDefinition;
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
	TArray<FString> Names;

	UPROPERTY(EditDefaultsOnly)
	FString Surname;
	
	UPROPERTY(EditDefaultsOnly)
	FString CallSign;

	UPROPERTY(EditDefaultsOnly)
	FString ShipName;

	UPROPERTY(EditDefaultsOnly)
	UShipClassDefinition* ShipClass;
	
	UPROPERTY(EditDefaultsOnly)
	UFactionDefinition* Faction;
	
	UPROPERTY(EditDefaultsOnly)
	UMaterialInstance* Portrait;
	
	UPROPERTY(EditDefaultsOnly)
	UMaterialInstance* FacePortrait;
};
