#pragma once

#include "CoreMinimal.h"

#include "CargoCategoryDefinition.h"
#include "AnythingToDeclare/Documents/CodexDataInterface.h"

#include <Engine/DataAsset.h>

#include "CargoDefinition.generated.h"

UCLASS(Blueprintable)
class UCargoTypeDefinition : public UDataAsset, public ICodexDataInterface
{
	GENERATED_BODY()
	
public:
	UCargoTypeDefinition()
		: RandomlySelectable(true)
		, ShowInCodex(true)
		, SelectionWeight(1.0f)
	{
	}

	virtual const FString& GetDataName() const override
	{
		return Name;
	}

	virtual const FString& GetDescription() const override
	{
		return Description;
	}

	virtual UMaterialInstance* GetIcon() const override
	{
		return Icon;
	}

	virtual const UDataAsset* GetParentData() const override
	{
		return Category;
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
