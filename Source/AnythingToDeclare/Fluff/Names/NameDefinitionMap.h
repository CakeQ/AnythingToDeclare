#pragma once

#include "CoreMinimal.h"

#include <Engine/DataAsset.h>
#include <Engine/DataTable.h>

#include "NameDefinitionMap.generated.h"

USTRUCT(BlueprintType)
struct FNameDefinitionData : public FTableRowBase
{
	GENERATED_BODY()

public:

	FNameDefinitionData()
		: Name(NAME_None)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Name)
	FName Name;
};

UCLASS(Blueprintable)
class UNameDefinitionMap : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	TMap<int32, float> NameComplexityModifiers;

	UPROPERTY(EditDefaultsOnly)
	TMap<int32, float> SurnameComplexityModifiers;

	UPROPERTY(EditDefaultsOnly)
	TMap<int32, float> CallSignComplexityModifiers;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<int32, float> ShipNameComplexityModifiers;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* Names;
	
	UPROPERTY(EditDefaultsOnly)
	UDataTable* Surnames;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* CallSignWords;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* ShipNamePrefixes;
	
	UPROPERTY(EditDefaultsOnly)
	UDataTable* ShipNameWords;
};
