#pragma once

#include "CoreMinimal.h"
#include "AnythingToDeclare/Documents/CargoManifest.h"

#include "UMG/Public/Blueprint/UserWidget.h"

#include "CargoManifestEntryWidget.generated.h"

class UTextBlock;

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
	UTextBlock* CargoUnits;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CargoWeight;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CargoValue;
};
