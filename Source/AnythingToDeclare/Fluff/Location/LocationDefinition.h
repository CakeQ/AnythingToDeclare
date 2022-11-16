#pragma once

#include "CoreMinimal.h"

#include <Engine/DataAsset.h>

#include "AnythingToDeclare/Documents/CodexDataInterface.h"
#include "LocationDefinition.generated.h"

class URegionDefinition;
class UCargoTypeDefinition;

UCLASS(Blueprintable)
class ULocationDefinition : public UDataAsset, public ICodexDataInterface
{
	GENERATED_BODY()
	
public:
	ULocationDefinition(const FObjectInitializer& ObjectInitializer)
		: Super(ObjectInitializer)
		, RandomlySelectable(true)
		, ShowInCodex(true)
		, PopularityModifier(1.0f)
	{
	}

	virtual const FString& GetDataName() const override;
	virtual const FString& GetDescription() const override;
	virtual const UDataAsset* GetParentData() const override;

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
	
	UPROPERTY(EditDefaultsOnly)
	URegionDefinition* Region;
};
