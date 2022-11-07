﻿#pragma once

#include "CoreMinimal.h"
#include "CustomsRequestModifier.h"
#include "CustomsRequestType.h"

#include "../Character/CharacterAppearanceDataAsset.h"
#include "../Documents/CargoManifest.h"

#include "CustomsRequest.generated.h"

class UFactionDefinition;
UENUM(BlueprintType)
enum class ECustomsRequestOutcome : uint8
{
	Pending,
	Approved,
	Denied
};

USTRUCT(BlueprintType)
struct FCustomsRequest
{
	GENERATED_BODY()
	
public:
	FCustomsRequest()
		: CharacterAppearance(nullptr)
		, CargoManifest()
		, RequestType(ECustomsRequestType::None)
		, Outcome(ECustomsRequestOutcome::Pending)
		, Faction(nullptr)
		, OriginLocation(nullptr)
		, DestinationLocation(nullptr)
	{};

	bool IsValid()
	{
		return RequestType != ECustomsRequestType::None;
	};
	
	UPROPERTY(VisibleAnywhere)
	UCharacterAppearanceDataAsset* CharacterAppearance;

	UPROPERTY(VisibleAnywhere)
	TArray<ECustomsRequestModifier> RequestModifiers;
	
	UPROPERTY(VisibleAnywhere)
	FCargoManifest CargoManifest;
	
	UPROPERTY(VisibleAnywhere)
	ECustomsRequestType RequestType;

	UPROPERTY(VisibleAnywhere)
	ECustomsRequestOutcome Outcome;

	UPROPERTY(VisibleAnywhere)
	UFactionDefinition* Faction;
	
	UPROPERTY(VisibleInstanceOnly)
	USubLocationDefinition* OriginLocation;

	UPROPERTY(VisibleInstanceOnly)
	USubLocationDefinition* DestinationLocation;
};