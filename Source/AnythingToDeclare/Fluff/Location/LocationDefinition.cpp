// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#include "LocationDefinition.h"

#include "RegionDefinition.h"

const FString& ULocationDefinition::GetDataName() const
{
	return Name;
}

const FString& ULocationDefinition::GetDescription() const
{
	return Description;
}

const UDataAsset* ULocationDefinition::GetParentData() const
{
	return Region;
}