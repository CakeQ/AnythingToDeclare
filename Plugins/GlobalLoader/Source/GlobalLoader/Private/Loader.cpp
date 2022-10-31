// Copyright Tom Shinton 2022 - GlobalLoader

#include "GlobalLoader/Public/Loader.h"

FLoader::FLoader()
	: PendingRequests()
	, StreamableManager()
{

}

FLoader::~FLoader()
{
	for (FBaseLoadRequest* Request : PendingRequests)
	{
		if (Request != nullptr)
		{
			Request->Cancel();
		}
	}
}

void FLoader::OnLoaded()
{
	for (int32 Request = PendingRequests.Num() - 1; Request >= 0; --Request)
	{
		if (FBaseLoadRequest* CurrRequest = PendingRequests[Request])
		{
			if (CurrRequest->IsComplete())
			{
				CurrRequest->TryResolve();
				PendingRequests.RemoveAt(Request);
			}
		}
	}
}
