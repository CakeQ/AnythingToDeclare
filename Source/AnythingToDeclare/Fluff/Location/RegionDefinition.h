#pragma once

#include "CoreMinimal.h"

#include <Engine/DataAsset.h>

#include "RegionDefinition.generated.h"

UCLASS(Blueprintable)
class URegionDefinition : public UDataAsset
{
	GENERATED_BODY()
	
public:
	URegionDefinition()
		: ShowInCodex(true)
		, PopularityModifier(1.0f)
	{
	}
	
	UPROPERTY(EditDefaultsOnly)
	bool ShowInCodex;
	
	UPROPERTY(EditDefaultsOnly)
	float PopularityModifier;
	
	UPROPERTY(EditDefaultsOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly)
	FString Description;
};
