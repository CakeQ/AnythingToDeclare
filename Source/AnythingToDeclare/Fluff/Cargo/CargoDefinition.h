#pragma once

#include "CoreMinimal.h"

#include <Engine/DataAsset.h>

#include "CargoDefinition.generated.h"

UCLASS(Blueprintable)
class UCargoTypeDefinition : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly)
	float WeightMultiplierPerUnit;
	
	UPROPERTY(EditDefaultsOnly, meta=(MetaClass="/Script/Engine.Texture"))
	FSoftClassPath Icon;

	UPROPERTY(EditDefaultsOnly)
	bool IsIllegal;
};
