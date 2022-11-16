﻿// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#include "RegionDefinition.h"

const FString& URegionDefinition::GetDataName() const
{
	return Name;
}

const FString& URegionDefinition::GetDescription() const
{
	return Description;
}

const UDataAsset* URegionDefinition::GetParentData() const
{
	return nullptr;
}
