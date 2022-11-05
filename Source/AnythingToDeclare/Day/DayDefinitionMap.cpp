// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/


#include "DayDefinitionMap.h"

#include "DayDefinition.h"

UDayDefinitionMap::UDayDefinitionMap()
{
}

const UDayDefinitionAsset* UDayDefinitionMap::FindDayNumber(const int32 InDayNumber) const
{
	for(const UDayDefinitionAsset* Definition : Days)
	{
		if(Definition != nullptr && Definition->DayNumber == InDayNumber)
		{
			return Definition;
		}
	}
	return nullptr;
}
