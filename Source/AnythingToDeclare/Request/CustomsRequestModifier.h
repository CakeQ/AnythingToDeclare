#pragma once

#include "CoreMinimal.h"

#include <UObject/ObjectMacros.h>

#include "CustomsRequestModifier.generated.h"

UENUM()
enum class ECustomsRequestModifier : uint8
{
	IllegalCargo,
	FakeDocument
};
