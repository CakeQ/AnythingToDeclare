#pragma once

#include "CoreMinimal.h"

#include <Engine/DataAsset.h>

#include "CargoCategoryDefinition.generated.h"

UCLASS(Blueprintable)
class UCargoCategoryDefinition : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UCargoCategoryDefinition()
		: SelectionWeight(1.0f)
	{
	}
	
	UPROPERTY(EditDefaultsOnly)
	float SelectionWeight;
	
	UPROPERTY(EditDefaultsOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly, meta=(MetaClass="/Script/Engine.Texture"))
	FSoftClassPath DefaultIcon;
};
