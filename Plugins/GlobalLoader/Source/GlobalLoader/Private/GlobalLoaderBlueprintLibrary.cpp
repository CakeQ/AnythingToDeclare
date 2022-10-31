// Copyright Tom Shinton 2022 - GlobalLoader

#include "GlobalLoader/Public/GlobalLoaderBlueprintLibrary.h"
#include "GlobalLoader/Public/Loader.h"

#include <Runtime/CoreUObject/Public/Templates/SubclassOf.h>

void UGlobalLoaderBlueprintLibrary::LoadObject(const FSoftObjectPath& InPath, UPARAM(DisplayName = "Object Loaded Event") FGloballyLoadObjectDelegate Delegate)
{
	FLoader::Load<UObject>(InPath, [Delegate](UObject& InLoadedObject)
	{
		Delegate.Execute(&InLoadedObject);
	});
}

void UGlobalLoaderBlueprintLibrary::LoadClass(const FSoftClassPath& InClassPath, UPARAM(DisplayName = "Class Loaded Event") FGloballyLoadClassDelegate Delegate)
{
	FLoader::Load<UObject>(InClassPath, [Delegate](const TSubclassOf<UObject>& InLoadedClass)
	{
		Delegate.Execute(InLoadedClass.Get());
	});
}
