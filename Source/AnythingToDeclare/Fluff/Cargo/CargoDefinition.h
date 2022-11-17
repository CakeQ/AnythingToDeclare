#pragma once

#include "CoreMinimal.h"

#include <Engine/DataAsset.h>

#include "CargoDefinition.generated.h"

class UCargoCategoryDefinition;

UCLASS(Blueprintable)
class UCargoTypeDefinition : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UCargoTypeDefinition()
		: RandomlySelectable(true)
		, ShowInCodex(true)
		, SelectionWeight(1.0f)
	{
	}
	
	UPROPERTY(EditDefaultsOnly)
	bool RandomlySelectable;
	
	UPROPERTY(EditDefaultsOnly)
	bool ShowInCodex;
	
	UPROPERTY(EditDefaultsOnly)
	bool IsIllegal;
	
	UPROPERTY(EditDefaultsOnly)
	float SelectionWeight;
	
	UPROPERTY(EditDefaultsOnly)
	float WeightMultiplierPerUnit;

	UPROPERTY(EditDefaultsOnly)
	float ValuePerUnit;
	
	UPROPERTY(EditDefaultsOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly)
	FString Description;
	
	UPROPERTY(EditDefaultsOnly)
	UCargoCategoryDefinition* Category;
	
	UPROPERTY(EditDefaultsOnly)
	UMaterialInstance* Icon;
};
