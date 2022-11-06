#pragma once

#include "CoreMinimal.h"

#include <Engine/DataAsset.h>

#include "SubLocationDefinition.generated.h"

class ULocationDefinition;
class UCargoTypeDefinition;

UCLASS(Blueprintable)
class USubLocationDefinition : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	float PopularityModifier;
	
	UPROPERTY(EditDefaultsOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly)
	TArray<UCargoTypeDefinition*> SuppliedCargoTypes;

	UPROPERTY(EditDefaultsOnly)
	TArray<UCargoTypeDefinition*> DemandedCargoTypes;

	UPROPERTY(EditDefaultsOnly)
	ULocationDefinition* Location;
};
