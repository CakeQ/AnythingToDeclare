// Copyright Tom Shinton 2022 - GlobalLoader

#pragma once

#include <Runtime/Engine/Classes/Engine/StreamableManager.h>

DEFINE_LOG_CATEGORY_STATIC(LoadRequestLog, Log, Log)

struct FBaseLoadRequest
{
public:

	FBaseLoadRequest(const TSharedPtr<FStreamableHandle>& InHandle)
		: Handle(InHandle)
	{};

	virtual ~FBaseLoadRequest() {};
	
	virtual bool TryResolve() const
	{
		return false;
	};

	bool IsComplete() const
	{
		return Handle->HasLoadCompleted();
	};

	void Cancel()
	{
		Handle->CancelHandle();
	}

protected:

	TSharedPtr<FStreamableHandle> Handle;
};

template<class TObjectRequest>
struct FObjectLoadRequest : public FBaseLoadRequest
{

public:
	
	FObjectLoadRequest()
		: FBaseLoadRequest(nullptr)
		, Callback(nullptr)
	{};

	FObjectLoadRequest(const TSharedPtr<FStreamableHandle>& InHandle, const TFunction<void(TObjectRequest&)>& InCallback)
		: FBaseLoadRequest(InHandle)
		, Callback(InCallback)
	{};

	//FBaseLoadRequest
	virtual bool TryResolve() const override final
	{
		if (Callback != nullptr)
		{
			if (UObject* LoadedObject = Handle->GetLoadedAsset())
			{
				Callback(*CastChecked<TObjectRequest>(LoadedObject));
				return true;
			}
		}

		return false;
	}
	//~FBaseLoadRequest

private:

	TFunction<void(TObjectRequest&)> Callback;
};

template<class TClassRequest>
struct FClassLoadRequest : public FBaseLoadRequest
{
public:

	FClassLoadRequest()
		: FBaseLoadRequest(nullptr)
		, Callback(nullptr)
	{};

	FClassLoadRequest(const TSharedPtr<FStreamableHandle>& InHandle, const TFunction<void(const TSubclassOf<TClassRequest>&)>& InCallback)
		: FBaseLoadRequest(InHandle)
		, Callback(InCallback)
	{};

	//FBaseLoadRequest
	virtual bool TryResolve() const override final
	{
		if (Callback != nullptr)
		{
			TArray<FSoftObjectPath> AssetList;
			Handle->GetRequestedAssets(AssetList);
			if (AssetList.IsValidIndex(0))
			{
				const FSoftClassPath AssetAsClass = FSoftClassPath(AssetList[0].ToString());
				if (UClass* Class = AssetAsClass.ResolveClass())
				{
					Callback(Class);
					return true;
				}
			}
		}

		return false;
	}
	//~FBaseLoadRequest

private:

	TFunction<void(const TSubclassOf<TClassRequest>&)> Callback;
};

