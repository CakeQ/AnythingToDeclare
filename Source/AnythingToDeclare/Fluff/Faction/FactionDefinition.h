#pragma once

#include "CoreMinimal.h"

#include "AnythingToDeclare/Fluff/Cargo/CargoDefinition.h"

#include <Engine/DataAsset.h>

#include "FactionDefinition.generated.h"

class UDataTable;

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
	FString Description;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<UCargoTypeDefinition*> CargoTypes;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<int32, float> NameComplexityModifiers;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* CharacterNames;
	
	UPROPERTY(EditDefaultsOnly)
	UDataTable* CharacterSurnames;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* CallSignWords;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* ShipNamePrefixes;
	
	UPROPERTY(EditDefaultsOnly)
	UDataTable* ShipNameWords;
	
	UPROPERTY(EditDefaultsOnly, meta=(MetaClass="/Script/Engine.Texture"))
	FSoftClassPath Icon;
};
