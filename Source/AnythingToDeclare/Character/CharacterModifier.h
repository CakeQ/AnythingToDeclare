#pragma once

#include "CoreMinimal.h"

#include <UObject/ObjectMacros.h>

#include "CharacterModifier.generated.h"

UENUM()
enum class ECharacterModifier : uint8
{
	IllegalCargo,
	FakeDocument
};
