#pragma once

#include "CoreMinimal.h"

#include <Engine/DataAsset.h>
#include <Engine/DataTable.h>

#include "NameDefinitionMap.generated.h"

UENUM(BlueprintType)
enum class ENameDefinitionType : uint8
{
	Noun,
	Adjective
};

USTRUCT(BlueprintType)
struct FNameDefinitionData : public FTableRowBase
{
	GENERATED_BODY()

public:

	FNameDefinitionData()
		: Name(NAME_None)
		, Type(ENameDefinitionType::Noun)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Name)
	FName Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Name)
	ENameDefinitionType Type;
};

UCLASS(Blueprintable)
class UNameDefinitionMap : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UNameDefinitionMap();
	
	virtual void PostLoad() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	void RegenerateDataLists();
	
	UPROPERTY(EditDefaultsOnly)
	int32 NamePriority;
	
	UPROPERTY(EditDefaultsOnly)
	int32 SurnamePriority;
	
	UPROPERTY(EditDefaultsOnly)
	int32 CallSignPriority;
	
	UPROPERTY(EditDefaultsOnly)
	int32 ShipNamePriority;
	
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

	UPROPERTY()
	TArray<FName> CallSignAdjectives;
	
	UPROPERTY()
	TArray<FName> CallSignNouns;
	
	UPROPERTY(EditDefaultsOnly)
	UDataTable* ShipNamePrefixes;
	
	UPROPERTY(EditDefaultsOnly)
	UDataTable* ShipNameWords;

	UPROPERTY()
	TArray<FName> ShipNameAdjectives;
	
	UPROPERTY()
	TArray<FName> ShipNameNouns;
};
