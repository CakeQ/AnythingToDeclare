// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/


#include "GameplayTagContextAsset.h"

const FGameplayTagContextData* UGameplayTagContextAsset::FindTagContextData(const FGameplayTag& RequestTag) const
{
	for(const FGameplayTagContextData& TagContextData : RequestModifiers)
	{
		if(TagContextData.Tag.MatchesTag(RequestTag))
		{
			return &TagContextData;
		}
	}
	return nullptr;
}
