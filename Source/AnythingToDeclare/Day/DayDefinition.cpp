// Copyright Daniel Thompson and Archie Whitehead

#include "DayDefinition.h"

#include "AnythingToDeclare/Character/CharacterAppearanceDataAsset.h"

const UCharacterAppearanceDataAsset* UDayDefinitionAsset::FindCharacterByAppearanceNumber(const int32 InNumber)
{
	for(const UCharacterAppearanceDataAsset* CharacterAppearance : CharacterAppearances)
	{
		if(CharacterAppearance->CharacterPosition == InNumber)
		{
			return CharacterAppearance;
		}
	}
	return nullptr;
}
