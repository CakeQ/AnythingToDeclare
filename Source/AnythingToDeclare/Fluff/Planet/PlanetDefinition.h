#pragma once

#include "CoreMinimal.h"

#include <Engine/DataAsset.h>

#include "PlanetDefinition.generated.h"

class UCargoTypeDefinition;

UCLASS(Blueprintable)
class UPlanetDefinition : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly, meta=(MetaClass="/Script/Engine.Texture"))
	FSoftClassPath Icon;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<UCargoTypeDefinition*> SuppliedCargoTypes;

	UPROPERTY(EditDefaultsOnly)
	TArray<UCargoTypeDefinition*> DemandedCargoTypes;
};
