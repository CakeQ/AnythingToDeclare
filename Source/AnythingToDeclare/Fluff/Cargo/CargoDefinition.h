#pragma once

#include "CoreMinimal.h"

#include <Engine/DataAsset.h>

#include "CargoDefinition.generated.h"

UCLASS(Blueprintable)
class UCargoTypeDefinition : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UCargoTypeDefinition()
		: RandomlySelectable(true)
	{
	}
	
	UPROPERTY(EditDefaultsOnly)
	bool RandomlySelectable;
	
	UPROPERTY(EditDefaultsOnly)
	bool IsIllegal;
	
	UPROPERTY(EditDefaultsOnly)
	float WeightMultiplierPerUnit;

	UPROPERTY(EditDefaultsOnly)
	float ValuePerUnit;
	
	UPROPERTY(EditDefaultsOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly, meta=(MetaClass="/Script/Engine.Texture"))
	FSoftClassPath Icon;
};
