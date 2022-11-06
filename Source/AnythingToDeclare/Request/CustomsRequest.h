#pragma once

#include "CoreMinimal.h"
#include "CustomsRequestModifier.h"
#include "CustomsRequestType.h"

#include "../Character/CharacterAppearanceDataAsset.h"
#include "../Documents/CargoManifest.h"

#include "CustomsRequest.generated.h"

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
		, OriginLocation(nullptr)
		, DestinationLocation(nullptr)
	{};
	
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

	UPROPERTY(VisibleInstanceOnly)
	USubLocationDefinition* OriginLocation;

	UPROPERTY(VisibleInstanceOnly)
	USubLocationDefinition* DestinationLocation;	
};