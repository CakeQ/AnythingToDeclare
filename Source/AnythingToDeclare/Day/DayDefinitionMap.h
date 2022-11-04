// Copyright Daniel Thompson and Archie Whitehead

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

	UFUNCTION()
	const UDayDefinitionAsset* FindDayNumber(const int32 InDayNumber) const;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<const UDayDefinitionAsset*> Days;
};
