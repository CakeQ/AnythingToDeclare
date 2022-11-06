#pragma once

#include "CoreMinimal.h"

#include "CustomsRequestType.generated.h"

UENUM(BlueprintType)
enum class ECustomsRequestType : uint8
{
	None,
	Outbound,
	Inbound,
	Transfer
};
