// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#pragma once

#include "CoreMinimal.h"

#include "Console/GenericConsole.h"
#include "Day/DayDefinition.h"
#include "Dialogue/DialogueMessage.h"
#include "GameFramework/GameStateBase.h"
#include "Request/CustomsRequest.h"

#include "AnythingToDeclareGameState.generated.h"

struct FDialogueDataTableRow;
class UGameplayTagContextAsset;
class UCustomsRequestConversationMonitorWidget;
class UCustomsRequestCodexMonitorWidget;
class UCodexWidget;
class UCustomsRequestMonitorWidget;
class UCustomsRequestDataMap;
class UDayDefinitionMap;
class UDayDefinitionAsset;

UCLASS()
class ANYTHINGTODECLARE_API AAnythingToDeclareGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AAnythingToDeclareGameState(const FObjectInitializer& InInitializer);

	virtual void BeginPlay() override;
	
	void StartDay(const int32 InDayNumber);

	UFUNCTION()
	void OnDayLoaded(const UDayDefinitionAsset* InDayAsset);

	UFUNCTION()
	void OnDayNotFound();

	UFUNCTION()
	void NextRequest();

	UFUNCTION()
	void OnRequestApproved();

	UFUNCTION()
	void OnRequestDenied();

	UFUNCTION()
	void OnQuestioned();

	static void GetMessageDataFromTable(const FGameplayTag& MessageType, const TArray<FGameplayTag>& InTags, const UDataTable* InTable, TArray<const
		                                    FDialogueDataTableRow*>& OutData);
	void GenerateMessageToSend(const FGameplayTag& MessageType, const TArray<FGameplayTag>& InTags, const float TimeToSend, const bool IsPlayer);
	void SendMessage(const FDialogueMessage& InMessage) const;
	
	UFUNCTION()
	AActor* CycleCameraNext();
	
	UFUNCTION()
	AActor* CycleCameraPrev();
	
private:
	UFUNCTION()
	void HandleRequest(const ECustomsRequestOutcome& InOutcome);
	
	UPROPERTY(VisibleAnywhere)
	int32 DayNumber;

	UPROPERTY(VisibleAnywhere)
	int32 CurrentRequestCount;

	int32 MaxCameraOrder;
	
	UPROPERTY(VisibleAnywhere)
	const UDayDefinitionAsset* CurrentDayDefinition;
	
	UPROPERTY()
	UDayDefinitionMap* DayDataMap;

	UPROPERTY()
	UCustomsRequestDataMap* CustomsDataMap;

	UPROPERTY()
	UGameplayTagContextAsset* GameplayTagContexts;

	UPROPERTY()
	TWeakObjectPtr<UCustomsRequestMonitorWidget> CachedRequestMonitorWidget;

	UPROPERTY()
	TWeakObjectPtr<UCustomsRequestCodexMonitorWidget> CachedCodexMonitorWidget;

	UPROPERTY()
	TWeakObjectPtr<UCustomsRequestConversationMonitorWidget> CachedConversationMonitorWidget;

	UPROPERTY()
	TWeakObjectPtr<AGenericConsole> FocusedConsole;
	
	UPROPERTY()
	TArray<TWeakObjectPtr<AGenericConsole>> Consoles;

	UPROPERTY()
	FCustomsRequest CurrentRequest;
	
	UPROPERTY()
	TArray<FCustomsRequest> ProcessedRequests;

	UPROPERTY()
	TArray<FTimerHandle> ConversationTimerHandles;
};
