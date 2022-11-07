#pragma once

#include "CoreMinimal.h"

#include <Engine/DataAsset.h>

#include "LocationDefinition.generated.h"

class UCargoTypeDefinition;

UCLASS(Blueprintable)
class ULocationDefinition : public UDataAsset
{
	GENERATED_BODY()
	
public:
	ULocationDefinition()
		: RandomlySelectable(true)
		, PopularityModifier(1.0f)
	{
	}
	
	UPROPERTY(EditDefaultsOnly)
	bool RandomlySelectable;
	
	UPROPERTY(EditDefaultsOnly)
	float PopularityModifier;
	
	UPROPERTY(EditDefaultsOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly, meta=(MetaClass="/Script/Engine.Texture"))
	FSoftClassPath Icon;
};
