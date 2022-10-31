// Copyright Tom Shinton 2022 - GlobalLoader

#pragma once

#include <Runtime/Core/Public/CoreMinimal.h>
#include <Runtime/Core/Public/Modules/ModuleInterface.h>

class FLoader;

namespace GlobalLoader
{
	const FName GlobalLoaderModuleName = TEXT("GlobalLoader");
}

class IGlobalLoaderInterface : public IModuleInterface
{
public:

	virtual TSharedPtr<FLoader> GetLoader() = 0;
};