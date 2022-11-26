// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "GameplayTagContextAsset.generated.h"

/**
 * 
 */
UCLASS()
class ANYTHINGTODECLARE_API UGameplayTagContextAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag GreetingTag;
	
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag CryogenicTag;
};
