#pragma once

#include "CoreMinimal.h"
#include "CustomsRequestModifier.h"
#include "CustomsRequestType.h"

#include "../Character/CharacterAppearanceDataAsset.h"
#include "../Documents/CargoManifest.h"
#include "AnythingToDeclare/Character/CharacterAppearance.h"
#include "AnythingToDeclare/Fluff/Ship/ShipClassDefinition.h"

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
		, Ship(nullptr)
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
	FCargoManifest CargoManifest;
	
	UPROPERTY(VisibleAnywhere)
	FCharacterAppearance Character;
	
	UPROPERTY(VisibleAnywhere)
	ECustomsRequestType RequestType;

	UPROPERTY(VisibleAnywhere)
	TArray<FGameplayTag> RequestTags;
	
	UPROPERTY(VisibleAnywhere)
	ECustomsRequestOutcome Outcome;

	UPROPERTY(VisibleAnywhere)
	UShipClassDefinition* Ship;
	
	UPROPERTY(VisibleAnywhere)
	UFactionDefinition* Faction;
	
	UPROPERTY(VisibleInstanceOnly)
	USubLocationDefinition* OriginLocation;

	UPROPERTY(VisibleInstanceOnly)
	USubLocationDefinition* DestinationLocation;
};