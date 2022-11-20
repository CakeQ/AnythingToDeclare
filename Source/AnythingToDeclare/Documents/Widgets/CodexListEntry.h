// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CodexListEntry.generated.h"

/**
 * 
 */
UCLASS()
class ANYTHINGTODECLARE_API UCodexListEntry : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	const TArray<UCodexListEntry*>& GetItemChildren() const { return Children; };
	
	UFUNCTION()
	void SetLinkedData(const UObject* InData);

	UFUNCTION()
	const UObject* GetLinkedData() const { return LinkedData; };
	
	UFUNCTION()
	void AddChildEntry(UCodexListEntry* InChild);

private:
	UPROPERTY()
	const UObject* LinkedData;

	UPROPERTY()
	TArray<UCodexListEntry*> Children;
};
