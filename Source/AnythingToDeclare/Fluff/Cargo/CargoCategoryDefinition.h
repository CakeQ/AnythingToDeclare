#pragma once

#include "CoreMinimal.h"

#include "AnythingToDeclare/Documents/CodexDataInterface.h"

#include <Engine/DataAsset.h>

#include "CargoCategoryDefinition.generated.h"

UCLASS(Blueprintable)
class UCargoCategoryDefinition : public UDataAsset, public ICodexDataInterface
{
	GENERATED_BODY()
	
public:
	UCargoCategoryDefinition()
		: SelectionWeight(1.0f)
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
		return DefaultIcon;
	}

	virtual const UDataAsset* GetParentData() const override
	{
		return nullptr;
	}
	
	UPROPERTY(EditDefaultsOnly)
	float SelectionWeight;
	
	UPROPERTY(EditDefaultsOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly)
	FString Description;
	
	UPROPERTY(EditDefaultsOnly)
	UMaterialInstance* DefaultIcon;
};
