// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "RequestTagContext.generated.h"

UENUM(BlueprintType)
enum class EGameplayTagContext : uint8
{
	None,
	ManifestShipName,
	ManifestOrigin,
	ManifestDestination,
	ManifestCargo,
	IDName,
	IDAge,
	IDAgeCryo,
	IDFaction,
};

UENUM(BlueprintType)
enum class EGameplayTagModifier : uint8
{
	Illegal,
	HiddenPartially,
	HiddenFully,
	NameSwapped,
	HasTypo,
	Fake
};

USTRUCT(BlueprintType)
struct FGameplayTagContextData
{
	GENERATED_BODY()

public:

	FGameplayTagContextData()
		: Tag()
		, Context(EGameplayTagContext::None)
		, Modifiers()
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Name)
	FGameplayTag Tag;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Name)
	EGameplayTagContext Context;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Name)
	TArray<EGameplayTagModifier> Modifiers;
};
