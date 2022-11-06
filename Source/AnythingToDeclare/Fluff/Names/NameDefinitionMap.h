#pragma once

#include "CoreMinimal.h"

#include <Engine/DataAsset.h>

#include "NameDefinitionMap.generated.h"

UCLASS(Blueprintable)
class UNameDefinitionMap : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FString> Names;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<int32, float> NameComplexityModifiers;

	UPROPERTY(EditDefaultsOnly)
	TArray<FString> Surnames;

	UPROPERTY(EditDefaultsOnly)
	TArray<FString> CallSignWords;

	UPROPERTY(EditDefaultsOnly)
	TMap<int32, float> CallSignComplexityModifiers;

	UPROPERTY(EditDefaultsOnly)
	TArray<FString> ShipNamePrefixes;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<FString> ShipNameWords;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<int32, float> ShipNameComplexityModifiers;
};
