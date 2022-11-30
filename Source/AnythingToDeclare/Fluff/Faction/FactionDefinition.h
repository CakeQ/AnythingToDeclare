#pragma once

#include "CoreMinimal.h"

#include "AnythingToDeclare/Fluff/Cargo/CargoDefinition.h"
#include "AnythingToDeclare/Fluff/Ship/ShipClassDefinition.h"

#include <Engine/DataAsset.h>

#include "FactionDefinition.generated.h"

class UDataTable;
class UNameDefinitionMap;

UCLASS(Blueprintable)
class ANYTHINGTODECLARE_API UFactionDefinition : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UFactionDefinition()
		: RandomlySelectable(true)
		, OnlyCarryPreferredCargo(false)
		, ShowInCodex(true)
		, AppearanceWeight(1.0f)
	{
	}
	
	UPROPERTY(EditDefaultsOnly)
	bool RandomlySelectable;
	
	UPROPERTY(EditDefaultsOnly)
	bool OnlyCarryPreferredCargo;

	UPROPERTY(EditDefaultsOnly)
	bool ShowInCodex;
	
	UPROPERTY(EditDefaultsOnly)
	float AppearanceWeight;
	
	UPROPERTY(EditDefaultsOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly)
	TArray<FString> NameTypos;
	
	UPROPERTY(EditDefaultsOnly)
	FString Description;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<UCargoTypeDefinition*> CargoTypes;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<UShipClassDefinition*> ShipClasses;

	UPROPERTY(EditDefaultsOnly)
	UNameDefinitionMap* FactionNameOverrides;
	
	UPROPERTY(EditDefaultsOnly)
	UMaterialInstance* Icon;
};
