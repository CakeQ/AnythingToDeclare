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
		, ShowInCodex(true)
		, PopularityModifier(1.0f)
	{
	}
	
	UPROPERTY(EditDefaultsOnly)
	bool RandomlySelectable;
	
	UPROPERTY(EditDefaultsOnly)
	bool ShowInCodex;
	
	UPROPERTY(EditDefaultsOnly)
	float PopularityModifier;
	
	UPROPERTY(EditDefaultsOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly)
	FString Description;
	
	UPROPERTY(EditDefaultsOnly, meta=(MetaClass="/Script/Engine.Texture"))
	FSoftClassPath Icon;
};
