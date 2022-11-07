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
		, ShowInCodex(true)
	{
	}
	
	UPROPERTY(EditDefaultsOnly)
	bool RandomlySelectable;
	
	UPROPERTY(EditDefaultsOnly)
	bool ShowInCodex;
	
	UPROPERTY(EditDefaultsOnly)
	bool IsIllegal;
	
	UPROPERTY(EditDefaultsOnly)
	float WeightMultiplierPerUnit;

	UPROPERTY(EditDefaultsOnly)
	float ValuePerUnit;
	
	UPROPERTY(EditDefaultsOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly)
	FString Description;
	
	UPROPERTY(EditDefaultsOnly, meta=(MetaClass="/Script/Engine.Texture"))
	FSoftClassPath Icon;
};
