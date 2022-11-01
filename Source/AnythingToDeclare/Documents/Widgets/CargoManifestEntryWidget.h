#pragma once

#include "CoreMinimal.h"

#include "UMG/Public/Blueprint/UserWidget.h"

#include "CargoManifestEntryWidget.generated.h"

class UTextBlock;
struct FCargoManifestEntry;

UCLASS(Abstract, Blueprintable)
class UCargoManifestEntryWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	virtual void SetCargoManifestEntry(const FCargoManifestEntry& InManifestEntry);
	
protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CargoTypeName;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CargoWeight;
};
