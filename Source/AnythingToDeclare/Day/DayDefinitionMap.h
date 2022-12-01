// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"
#include "UObject/Object.h"

#include "DayDefinitionMap.generated.h"

class UDayDefinitionAsset;

/**
 * 
 */
UCLASS()
class ANYTHINGTODECLARE_API UDayDefinitionMap : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UDayDefinitionMap();

	virtual void PostLoad() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	void RegenerateDataLists();

	void OnDayAssetLoaded(const UDayDefinitionAsset* LoadedAsset);
	
	UFUNCTION()
	const UDayDefinitionAsset* FindDayNumber(const int32 InDayNumber) const;

private:
	UPROPERTY(EditDefaultsOnly)
	FDirectoryPath DaysFolder;

	UPROPERTY()
	TArray<const UDayDefinitionAsset*> Days;
};
