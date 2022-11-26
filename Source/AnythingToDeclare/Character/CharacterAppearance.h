#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"
#include "UObject/ObjectMacros.h"

#include "CharacterAppearance.generated.h"

USTRUCT()
struct FCharacterAppearance
{
	GENERATED_BODY()
public:

	FCharacterAppearance()
		: Age(0)
		, CryogenicAge(0)
		, Name()
		, Surname()
		, Portrait(nullptr)
		, FacePortrait(nullptr)
		, CurrentTags()
	{
	}
	
	UPROPERTY()
	int32 Age;

	UPROPERTY()
	int32 CryogenicAge;
	
	UPROPERTY()
	FString Name;

	UPROPERTY()
	FString Surname;
	
	UPROPERTY()
	FString CallSign;

	UPROPERTY()
	FString ShipName;

	UPROPERTY()
	UMaterialInstance* Portrait;
	
	UPROPERTY()
	UMaterialInstance* FacePortrait;

	TArray<FGameplayTag> CurrentTags;
};
