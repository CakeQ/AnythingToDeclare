#pragma once

#include "CoreMinimal.h"

#include <Engine/DataAsset.h>

#include "AnythingToDeclare/Documents/CodexDataInterface.h"
#include "SubLocationDefinition.generated.h"

class ULocationDefinition;
class UCargoTypeDefinition;

UCLASS(Blueprintable)
class USubLocationDefinition : public UDataAsset, public ICodexDataInterface
{
	GENERATED_BODY()
	
public:
	USubLocationDefinition(const FObjectInitializer& ObjectInitializer)
		: Super(ObjectInitializer)
		, RandomlySelectable(true)
		, ShowInCodex(true)
		, PopularityModifier(1.0f)
	{
	}

	virtual const FString& GetDataName() const override;
	virtual const FString& GetDescription() const override;
	// virtual const FTexture& GetIcon() const override;
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
	
	UPROPERTY(EditDefaultsOnly)
	TArray<UCargoTypeDefinition*> SuppliedCargoTypes;

	UPROPERTY(EditDefaultsOnly)
	TArray<UCargoTypeDefinition*> DemandedCargoTypes;

	UPROPERTY(EditDefaultsOnly, meta=(MetaClass="/Script/Engine.Texture"))
	FSoftClassPath Icon;
	
	UPROPERTY(EditDefaultsOnly)
	ULocationDefinition* Location;
};
