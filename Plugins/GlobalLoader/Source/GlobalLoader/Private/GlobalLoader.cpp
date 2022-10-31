// Copyright Tom Shinton 2022 - GlobalLoader

#include "GlobalLoader/Public/GlobalLoader.h"

DEFINE_LOG_CATEGORY_STATIC(GlobalLoaderModuleLog, Log, Log)

FGlobalLoaderModule::FGlobalLoaderModule()
	: GlobalLoader(MakeShareable<FLoader>(new FLoader()))
{
}

void FGlobalLoaderModule::StartupModule()
{
	UE_LOG(GlobalLoaderModuleLog, Log, TEXT("Initialising Global Loader"));
}

void FGlobalLoaderModule::ShutdownModule()
{
	UE_LOG(GlobalLoaderModuleLog, Log, TEXT("Uninitialising Global Loader"));
	GlobalLoader.Reset();
}
	
TSharedPtr<FLoader> FGlobalLoaderModule::GetLoader()
{
	return GlobalLoader;
}

IMPLEMENT_MODULE(FGlobalLoaderModule, GlobalLoader)

