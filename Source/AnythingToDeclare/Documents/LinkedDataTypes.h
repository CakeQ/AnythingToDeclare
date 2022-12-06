// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "LinkedDataTypes.generated.h"

USTRUCT(BlueprintType)
struct FLinkedDataString
{
	GENERATED_BODY()

public:
	FLinkedDataString()
		: Value()
		, Tags()
		, LinkedData()
	{}
	
	FLinkedDataString(const FString& InValue, const TArray<FGameplayTag>& InTags, const UObject* InLinkedData)
		: Value(InValue)
		, Tags(InTags)
		, LinkedData(InLinkedData)
	{}

	UPROPERTY()
	FString Value;

	UPROPERTY()
	TArray<FGameplayTag> Tags;

	UPROPERTY()
	const UObject* LinkedData;
};

USTRUCT(BlueprintType)
struct FLinkedDataFloat
{
	GENERATED_BODY()

public:
	FLinkedDataFloat()
		: Value()
		, Tags()
		, LinkedData()
	{}
	
	FLinkedDataFloat(const float InValue, const TArray<FGameplayTag>& InTags, const UObject* InLinkedData)
		: Value(InValue)
		, Tags(InTags)
		, LinkedData(InLinkedData)
	{}

	UPROPERTY()
	float Value;

	UPROPERTY()
	TArray<FGameplayTag> Tags;

	UPROPERTY()
	const UObject* LinkedData;
};

USTRUCT(BlueprintType)
struct FLinkedDataInt
{
	GENERATED_BODY()

public:
	FLinkedDataInt()
		: Value()
		, Tags()
		, LinkedData()
	{}
	
	FLinkedDataInt(const int32 InValue, const TArray<FGameplayTag>& InTags, const UObject* InLinkedData)
		: Value(InValue)
		, Tags(InTags)
		, LinkedData(InLinkedData)
	{}

	UPROPERTY()
	int32 Value;

	UPROPERTY()
	TArray<FGameplayTag> Tags;

	UPROPERTY()
	const UObject* LinkedData;
};
