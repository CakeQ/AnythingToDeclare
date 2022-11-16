// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CodexDataInterface.generated.h"

UINTERFACE()
class ANYTHINGTODECLARE_API UCodexDataInterface : public UInterface
{
	GENERATED_BODY()
};

class ANYTHINGTODECLARE_API ICodexDataInterface
{
	GENERATED_IINTERFACE_BODY()

public:
	UFUNCTION()
	virtual const FString& GetDataName() const = 0;

	UFUNCTION()
	virtual const FString& GetDescription() const = 0;
	
	// UFUNCTION()
	// virtual const FTexture& GetIcon() const = 0;

	UFUNCTION()
	virtual const UDataAsset* GetParentData() const = 0;
};
