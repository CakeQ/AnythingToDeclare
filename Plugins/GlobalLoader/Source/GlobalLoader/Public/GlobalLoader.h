// Copyright Tom Shinton 2022 - GlobalLoader

#pragma once

#include <Runtime/Core/Public/CoreMinimal.h>

#include "GlobalLoader/Public/GlobalLoaderInterface.h"
#include "GlobalLoader/Public/Loader.h"

class FGlobalLoaderModule : public IGlobalLoaderInterface
{
public:

	FGlobalLoaderModule();

	//IModuleInterface 
	virtual void StartupModule() override final;
	virtual void ShutdownModule() override final;
	//~IModuleInterface

	//IGlobalLoaderInterface
	virtual TSharedPtr<FLoader> GetLoader() override final;
	//~IGlobalLoaderInterface

private:

	TSharedPtr<FLoader> GlobalLoader;
};
