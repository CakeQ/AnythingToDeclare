// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#pragma once

#include "CoreMinimal.h"

class USubLocationDefinition;
class UCodexWidget;

namespace CodexWidgetHelper
{
	void GenerateCodexListFromRegions(UCodexWidget* CodexWidget, const TArray<USubLocationDefinition*> SubLocations);
}
