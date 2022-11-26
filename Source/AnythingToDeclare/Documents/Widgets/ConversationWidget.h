// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#pragma once

#include "CoreMinimal.h"
#include "AnythingToDeclare/Request/CustomsRequest.h"
#include "Blueprint/UserWidget.h"
#include "UObject/Object.h"
#include "ConversationWidget.generated.h"

class UConversationEntryWidget;
class UScrollBox;

/**
 * 
 */
UCLASS()
class ANYTHINGTODECLARE_API UConversationWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	
	void AddDialogue(const FText& InText, const FText& InName, UMaterialInstance* InIcon, const bool IsPlayer);
	void ClearConversation() const;
	void EndConversation(const ECustomsRequestOutcome InOutcome);

private:
	UPROPERTY(meta = (BindWidget))
	UScrollBox* ConversationLog;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UConversationEntryWidget> NPCEntryWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UConversationEntryWidget> PlayerEntryWidget;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> ApprovedWidget;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> DeniedWidget;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> EndWidget;
};
