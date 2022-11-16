// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#include "LocationDefinition.h"

#include "SubLocationDefinition.h"

const FString& USubLocationDefinition::GetDataName() const
{
	return Name;
}

const FString& USubLocationDefinition::GetDescription() const
{
	return Description;
}

// const FTexture& USubLocationDefinition::GetIcon() const
// {
// 	return Icon;
// }

const UDataAsset* USubLocationDefinition::GetParentData() const
{
	return Location;
}