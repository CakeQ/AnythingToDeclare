// Copyright Tom Shinton 2022 - GlobalLoader

#pragma once

#include <Runtime/Core/Public/CoreMinimal.h>

#include <Runtime/Core/Public/Templates/SharedPointer.h>
#include <Runtime/Core/Public/Modules/ModuleManager.h>
#include <Runtime/Engine/Classes/Engine/StreamableManager.h>

#include "GlobalLoader/Public/LoadRequest.h"
#include "GlobalLoader/Public/GlobalLoaderInterface.h"

DEFINE_LOG_CATEGORY_STATIC(GlobalLoaderLog, Log, All)

class FLoader : public TSharedFromThis<FLoader>
{

public:

	FLoader();
	~FLoader();

	template<class TLoadedObject>
	static void Load(const FSoftObjectPath& InPath, const TFunction<void(TLoadedObject&)>& InCallback)
	{
		if (!InPath.IsNull())
		{
			if (InCallback != nullptr)
			{
				IGlobalLoaderInterface& GlobalLoaderInterface = FModuleManager::GetModuleChecked<IGlobalLoaderInterface>(GlobalLoader::GlobalLoaderModuleName);
				if (TSharedPtr<FLoader> Loader = GlobalLoaderInterface.GetLoader())
				{
					Loader->LoadInternal<TLoadedObject>(InPath, InCallback);
				}
			}
			else
			{
				UE_LOG(GlobalLoaderLog, Error, TEXT("Cannot request load - provided callback is null"));
			}
		}
		else
		{
			UE_LOG(GlobalLoaderLog, Error, TEXT("Cannot request load - provided Object Path is null"));
		}
	}

	template<class TLoadedClass>
	static void Load(const FSoftClassPath& InPath, const TFunction<void(const TSubclassOf<TLoadedClass>&)>& InCallback)
	{
		if (!InPath.IsNull())
		{
			if (InCallback != nullptr)
			{
				IGlobalLoaderInterface& GlobalLoaderInterface = FModuleManager::GetModuleChecked<IGlobalLoaderInterface>(GlobalLoader::GlobalLoaderModuleName);
				if (TSharedPtr<FLoader> Loader = GlobalLoaderInterface.GetLoader())
				{
					Loader->LoadInternal<TLoadedClass>(InPath, InCallback);
				}
			}
			else
			{
				UE_LOG(GlobalLoaderLog, Error, TEXT("Cannot request load - provided callback is null"));
			}
		}
		else
		{
			UE_LOG(GlobalLoaderLog, Error, TEXT("Cannot request load - provided Class Path is null"));
		}
	}

private:

	template<class TLoadedObject>
	void LoadInternal(const FSoftObjectPath& InPath, const TFunction<void(TLoadedObject&)>& InCallback)
	{
		if (FBaseLoadRequest* NewRequest = new FObjectLoadRequest<TLoadedObject>(StreamableManager.RequestAsyncLoad(InPath, FStreamableDelegate::CreateSP(this, &FLoader::OnLoaded)), InCallback))
		{
			PendingRequests.Add(NewRequest);
		}
	}

	template<class TLoadedClass>
	void LoadInternal(const FSoftClassPath& InPath, const TFunction<void(const TSubclassOf<TLoadedClass>&)>& InCallback)
	{
		if (FBaseLoadRequest* NewRequest = new FClassLoadRequest<TLoadedClass>(StreamableManager.RequestAsyncLoad(InPath, FStreamableDelegate::CreateSP(this, &FLoader::OnLoaded)), InCallback))
		{
			PendingRequests.Add(NewRequest);
		}
	}

	GLOBALLOADER_API void OnLoaded();

	TArray<FBaseLoadRequest*> PendingRequests;
	FStreamableManager StreamableManager;
};