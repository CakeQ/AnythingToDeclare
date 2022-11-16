#pragma once

#include "CoreMinimal.h"

#include <Engine/DataAsset.h>

#include "AnythingToDeclare/Documents/CodexDataInterface.h"
#include "RegionDefinition.generated.h"

UCLASS(Blueprintable)
class URegionDefinition : public UDataAsset, public ICodexDataInterface
{
	GENERATED_BODY()
	
public:
	URegionDefinition(const FObjectInitializer& ObjectInitializer)
		: Super(ObjectInitializer)
		, ShowInCodex(true)
		, PopularityModifier(1.0f)
	{
	}

	virtual const FString& GetDataName() const override;
	virtual const FString& GetDescription() const override;
	virtual const UDataAsset* GetParentData() const override;

	UPROPERTY(EditDefaultsOnly)
	bool ShowInCodex;
	
	UPROPERTY(EditDefaultsOnly)
	float PopularityModifier;
	
	UPROPERTY(EditDefaultsOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly)
	FString Description;
};
