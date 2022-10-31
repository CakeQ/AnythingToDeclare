// Copyright Tom Shinton 2022 - GlobalLoader

#pragma once

#include <Runtime/Core/Public/CoreMinimal.h>
#include <Runtime/Engine/Classes/Kismet/BlueprintFunctionLibrary.h>
#include <Runtime/CoreUObject/Public/UObject/Object.h>

#include "GlobalLoaderBlueprintLibrary.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FGloballyLoadObjectDelegate, UObject*, LoadedObject);
DECLARE_DYNAMIC_DELEGATE_OneParam(FGloballyLoadClassDelegate, UClass*, LoadedClass);

UCLASS()
class GLOBALLOADER_API UGlobalLoaderBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category = "Global Loader", meta=(DisplayName="Load Object ASync", Tooltip = "Convert SoftObjectPath into usable UObject Pointer using Global Loader"))
	static void LoadObject(const FSoftObjectPath& InObjectPath, UPARAM(DisplayName = "Object Loaded Event") FGloballyLoadObjectDelegate Delegate);

	UFUNCTION(BlueprintCallable, Category = "Global Loader", meta = (DisplayName = "Load Class ASync", Tooltip = "Convert SoftClassPath into usable UClass using Global Loader"))
	static void LoadClass(const FSoftClassPath& InClassPath, UPARAM(DisplayName = "Class Loaded Event") FGloballyLoadClassDelegate Delegate);
};
