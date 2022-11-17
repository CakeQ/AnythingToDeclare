#pragma once

#include "CoreMinimal.h"

#include <Engine/DataAsset.h>

#include "ShipClassDefinition.generated.h"

class UFactionDefinition;

UCLASS(Blueprintable)
class ANYTHINGTODECLARE_API UShipClassDefinition : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UShipClassDefinition()
		: RandomlySelectable(true)
		, ShowInCodex(true)
		, UnitCapacity(100)
		, MaximumWeight(500.0f)
		, AppearanceWeight(1.0f)
	{
	}
	
	UPROPERTY(EditDefaultsOnly)
	bool RandomlySelectable;

	UPROPERTY(EditDefaultsOnly)
	bool ShowInCodex;
	
	UPROPERTY(EditDefaultsOnly)
	int32 UnitCapacity;
	
	UPROPERTY(EditDefaultsOnly)
	float MaximumWeight;
	
	UPROPERTY(EditDefaultsOnly)
	float AppearanceWeight;
	
	UPROPERTY(EditDefaultsOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly)
	UFactionDefinition* Manufacturer;
	
	UPROPERTY(EditDefaultsOnly, meta=(MetaClass="/Script/Engine.MaterialInstance"))
	FSoftClassPath Icon;
};
