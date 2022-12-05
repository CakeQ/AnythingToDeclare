// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#include "AnythingToDeclareGameState.h"

#include "AnythingToDeclareDeveloperSettings.h"
#include "Day/DayDefinitionMap.h"
#include "Request/CustomsRequestDataMap.h"
#include "Loader.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Camera/CameraActor.h"
#include "Dialogue/DialogueDataTableRow.h"
#include "Dialogue/DialogueMessage.h"
#include "Dialogue/DialogueQuestion.h"
#include "Documents/Widgets/CodexWidgetHelpers.h"
#include "Documents/Widgets/ConversationWidget.h"
#include "Documents/Widgets/QuestionHighlightBox.h"
#include "Documents/Widgets/Interfaces/QuestionContextGetterInterface.h"
#include "Documents/Widgets/Interfaces/QuestionContextInterface.h"
#include "Engine/DataTable.h"
#include "Kismet/GameplayStatics.h"
#include "Request/CustomsRequestGenerator.h"
#include "Settings/GameplayTagContextAsset.h"
#include "Widgets/CustomsRequestCodexMonitorWidget.h"
#include "Widgets/CustomsRequestConversationMonitorWidget.h"
#include "Widgets/CustomsRequestMonitorWidget.h"

namespace
{
	namespace AnythingToDeclareGameSatePrivates
	{
		const FString DialogueGenerationContextString(TEXT("AAnythingToDeclareGameState::GenerateMessageToSend"));
	}
}

AAnythingToDeclareGameState::AAnythingToDeclareGameState(const FObjectInitializer& InInitializer)
	: Super(InInitializer)
	, DayNumber(1)
	, CurrentRequestCount(0)
{
}

void AAnythingToDeclareGameState::BeginPlay()
{
	Super::BeginPlay();

	if(const UAnythingToDeclareDeveloperSettings* DeveloperSettings = UAnythingToDeclareDeveloperSettings::Get())
	{
		FLoader::Load<UDayDefinitionMap>(DeveloperSettings->DayDefinitionDataMap, [this](UDayDefinitionMap& InLoadedDataMap)
		{
			DayDataMap = &InLoadedDataMap;
			if(CustomsDataMap != nullptr && GameplayTagContexts != nullptr)
			{
				StartDay(1);
			}
		});

		FLoader::Load<UCustomsRequestDataMap>(DeveloperSettings->CustomsDataMap, [this](UCustomsRequestDataMap& InLoadedDataMap)
		{
			CustomsDataMap = &InLoadedDataMap;
			if(DayDataMap != nullptr && GameplayTagContexts != nullptr)
			{
				StartDay(1);
			}
			if(const UCustomsRequestCodexMonitorWidget* CodexMonitorWidget = CachedCodexMonitorWidget.Get())
			{
				CodexWidgetHelper::GenerateCodexListFromSubLocations(CodexMonitorWidget->LocationCodex, InLoadedDataMap.SubLocations);
				CodexWidgetHelper::GenerateCodexListFromCargoDefinitions(CodexMonitorWidget->CargoCodex, InLoadedDataMap.CargoTypes);
			}
		});

		FLoader::Load<UGameplayTagContextAsset>(DeveloperSettings->GameplayTagContexts, [this](UGameplayTagContextAsset& InLoadedContexts)
		{
			GameplayTagContexts = &InLoadedContexts;
			for(const FQuestionTagContextData& QuestionTagContextData : GameplayTagContexts->QuestionContexts)
			{
				if(QuestionTagContextData.TagRequirements.Num() > MaxHighlights)
				{
					MaxHighlights = QuestionTagContextData.TagRequirements.Num();
				}
			}
			if(DayDataMap != nullptr && CustomsDataMap != nullptr)
			{
				StartDay(1);
			}
		});
	}

	TArray<AActor*> WorldConsoles;	
	UGameplayStatics::GetAllActorsOfClass(this, AGenericConsole::StaticClass(), WorldConsoles);
	for(AActor* Console : WorldConsoles)
	{
		if(AGenericConsole* ConsolePtr = static_cast<AGenericConsole*>(Console))
		{
			MaxCameraOrder = ConsolePtr->GetCameraOrder() > MaxCameraOrder ? ConsolePtr->GetCameraOrder() : MaxCameraOrder;
			Consoles.Add(ConsolePtr);
			
			if(const UWidgetComponent* WidgetComponent = ConsolePtr->GetScreenWidget())
			{
				if(UCustomsRequestMonitorWidget* RequestMonitorWidget = Cast<UCustomsRequestMonitorWidget>(WidgetComponent->GetWidget()))
				{
					CachedRequestMonitorWidget = RequestMonitorWidget;
					if(const UCustomsActionsBar* ActionBar = RequestMonitorWidget->ActionBar)
					{
						if(ActionBar->AllowButton != nullptr)
						{
							ActionBar->AllowButton->OnConfirmed.AddDynamic(this, &AAnythingToDeclareGameState::OnRequestApproved);
						}
						if(ActionBar->DenyButton != nullptr)
						{
							ActionBar->DenyButton->OnConfirmed.AddDynamic(this, &AAnythingToDeclareGameState::OnRequestDenied);
						}
						if(ActionBar->QuestionButton != nullptr)
						{
							ActionBar->QuestionButton->OnReleased.AddDynamic(this, &AAnythingToDeclareGameState::OnQuestioned);
							CachedQuestionButton = ActionBar->QuestionButton;
						}
					}
				}
				
				if(UCustomsRequestCodexMonitorWidget* CodexMonitorWidget = Cast<UCustomsRequestCodexMonitorWidget>(WidgetComponent->GetWidget()))
				{
					CachedCodexMonitorWidget = CodexMonitorWidget;
				}
				
				if(UCustomsRequestConversationMonitorWidget* ConversationMonitorWidget = Cast<UCustomsRequestConversationMonitorWidget>(WidgetComponent->GetWidget()))
				{
					CachedConversationMonitorWidget = ConversationMonitorWidget;
				}
			}
		}
	}
}

void AAnythingToDeclareGameState::StartDay(const int32 InDayNumber)
{
	DayNumber = InDayNumber;
	CurrentRequestCount = 1;
	if(DayDataMap != nullptr)
	{
		if(const UDayDefinitionAsset* DayDefinitionAsset = DayDataMap->FindDayNumber(InDayNumber))
		{
			OnDayLoaded(DayDefinitionAsset);
		}
		else
		{
			OnDayNotFound();
		}
	}
	else
	{
		OnDayNotFound();
	}
}

void AAnythingToDeclareGameState::OnDayLoaded(const UDayDefinitionAsset* InDayAsset)
{
	CurrentDayDefinition = InDayAsset;
	NextRequest();
}

void AAnythingToDeclareGameState::OnDayNotFound()
{
	// Use default day
}

void AAnythingToDeclareGameState::NextRequest()
{
	CurrentRequestCount++;
	CurrentRequest = FCustomsRequest();
	for(UCharacterAppearanceDataAsset* Appearance : CurrentDayDefinition->CharacterAppearances)
	{
		if(Appearance->CharacterPosition == CurrentRequestCount)
		{
			CurrentRequest.CharacterAppearance = Appearance;
		}
	}

	CustomsRequestsHelper::GenerateRequest(CurrentRequest, CustomsDataMap, GameplayTagContexts, CurrentDayDefinition);
	if(const UCustomsRequestMonitorWidget* RequestMonitorWidget = CachedRequestMonitorWidget.Get())
	{
		if(RequestMonitorWidget->ManifestWidget != nullptr)
		{
			RequestMonitorWidget->ManifestWidget->SetCargoManifest(CurrentRequest.CargoManifest);
		}
	}

	TArray<UUserWidget*> QuestionContextWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsWithInterface(this, QuestionContextWidgets, UQuestionContextGetterInterface::StaticClass(), false);
	for(UUserWidget* Widget : QuestionContextWidgets)
	{
		if(const IQuestionContextGetterInterface* QuestionContextGetterInterface = Cast<IQuestionContextGetterInterface>(Widget))
		{
			TArray<UObject*> OutContexts;
			QuestionContextGetterInterface->GetQuestionContextData(OutContexts);

			for(UObject* ContextObject : OutContexts)
			{
				if(IQuestionContextInterface* QuestionContextInterface = Cast<IQuestionContextInterface>(ContextObject))
				{
					static const FName BinderFunction(TEXT("OnQuestionContextHighlighted"));
					QuestionContextInterface->BindQuestionHighlighting(this, BinderFunction);
				}
			}
		}
	}
	
	for(UQuestionHighlightBox* HighlightedText : HighlightedTextBlocks)
	{
		HighlightedText->SetCheckedState(ECheckBoxState::Unchecked);
	}
	HighlightedTextBlocks.Empty(MaxHighlights);
	
	GenerateMessageToSend(GameplayTagContexts->GreetingTag, CurrentRequest.Character.CurrentTags, 1.0f, false);
}

void AAnythingToDeclareGameState::OnRequestApproved()
{
	HandleRequest(ECustomsRequestOutcome::Approved);
}

void AAnythingToDeclareGameState::OnRequestDenied()
{
	HandleRequest(ECustomsRequestOutcome::Denied);
}

void AAnythingToDeclareGameState::OnQuestioned()
{
	FDialogueQuestion QuestionData;
	for(UQuestionHighlightBox* HighlightedText : HighlightedTextBlocks)
	{
		HighlightedText->GetQuestionContextData(QuestionData);
		HighlightedText->SetCheckedState(ECheckBoxState::Unchecked);
	}
	if(const FQuestionTagContextData* FoundContextData = GameplayTagContexts->FindQuestionTagContextData(QuestionData))
	{
		GenerateMessageToSend(FoundContextData->DialogueTag, PlayerTags, 0.5f, true);
		GenerateMessageToSend(FoundContextData->ResponseTag, CurrentRequest.Character.CurrentTags, 2.0f, false);
	}
	HighlightedTextBlocks.Empty(MaxHighlights);
}

void AAnythingToDeclareGameState::OnQuestionContextHighlighted(const bool IsHighlighted,
	UQuestionHighlightBox* InWidget)
{
	if(HighlightedTextBlocks.Contains(InWidget) && !IsHighlighted)
	{
		HighlightedTextBlocks.Remove(InWidget);
	}
	else if(IsHighlighted)
	{
		HighlightedTextBlocks.AddUnique(InWidget);
		if(HighlightedTextBlocks.Num() > MaxHighlights)
		{
			if(UQuestionHighlightBox* HighlightToRemove = HighlightedTextBlocks[0])
			{
				HighlightToRemove->SetCheckedState(ECheckBoxState::Unchecked);
			}
			HighlightedTextBlocks.RemoveAt(0);
		}
	}
}

void AAnythingToDeclareGameState::GetMessageDataFromTable(const FGameplayTag& MessageType,
                                                          const TArray<FGameplayTag>& InTags, const UDataTable* InTable, TArray<const FDialogueDataTableRow*>& OutData)
{
	if(InTable != nullptr)
	{
		TArray<FDialogueDataTableRow*> DialogueData;
		InTable->GetAllRows<FDialogueDataTableRow>(AnythingToDeclareGameSatePrivates::DialogueGenerationContextString, DialogueData);

		for(const FDialogueDataTableRow* DialogueDataRow : DialogueData)
		{
			if(DialogueDataRow->DialogueTag.MatchesTag(MessageType))
			{
				if(DialogueDataRow->Requirement.IsValid())
				{
					for(const FGameplayTag& InTag : InTags)
					{
						if(InTag.MatchesTag(DialogueDataRow->Requirement))
						{
							OutData.Add(DialogueDataRow);
							break;
						}
					}
				}
				else
				{
					OutData.Add(DialogueDataRow);
				}
			}
		}
	}
}

void AAnythingToDeclareGameState::GenerateMessageToSend(const FGameplayTag& MessageType, const TArray<FGameplayTag>& InTags, const float TimeToSend,
                                                        const bool IsPlayer)
{
	FGameplayTag MessageTagOverride = MessageType;

	for(const FGameplayTag& InTag : InTags)
	{
		if(InTag.MatchesTag(MessageType))
		{
			MessageTagOverride = InTag;
		}
	}
	
	if(const UWorld* World = GetWorld())
	{
		FDialogueMessage MessageToSend;

		TArray<const FDialogueDataTableRow*> FoundMatchingData;
		// Get dialogue data specific to character appearance
		if(CurrentRequest.CharacterAppearance != nullptr && CurrentRequest.CharacterAppearance->Dialogue != nullptr)
		{
			GetMessageDataFromTable(MessageTagOverride, InTags, CurrentRequest.CharacterAppearance->Dialogue, FoundMatchingData);
		}
		// If no character specific dialogue, use generic table
		if(FoundMatchingData.IsEmpty())
		{
			GetMessageDataFromTable(MessageTagOverride, InTags, CustomsDataMap->DefaultDialogue, FoundMatchingData);
		}

		if(!FoundMatchingData.IsEmpty())
		{
			FDialogueMessage Message;

			// Compile a list of all tag requirements that matched
			TArray<const FGameplayTag*> TagsToPickFrom;
			for(const FDialogueDataTableRow* DialogueDataTableRow : FoundMatchingData)
			{
				if(DialogueDataTableRow->Requirement.IsValid())
				{
					TagsToPickFrom.AddUnique(&DialogueDataTableRow->Requirement);
				}
			}

			// If there were some dialogue options with tag requirements, pick one to use and filter out all dialogue that doesn't have said requirement
			if(!TagsToPickFrom.IsEmpty())
			{
				if(const FGameplayTag* TagFilter = TagsToPickFrom[FMath::RandRange(0, TagsToPickFrom.Num() - 1)]; TagFilter != nullptr)
				{
					for(int32 i = FoundMatchingData.Num() - 1; i > 0; i--)
					{
						if(const FDialogueDataTableRow* DialogueDataTableRow = FoundMatchingData[i]; !DialogueDataTableRow->Requirement.MatchesTagExact(*TagFilter))
						{
							FoundMatchingData.Remove(DialogueDataTableRow);
						}
					}
				}
			}

			// Finally, pick a dialogue option to use
			if(!FoundMatchingData.IsEmpty())
			{
				if(const FDialogueDataTableRow* ChosenDialogue = FoundMatchingData[FMath::RandRange(0, FoundMatchingData.Num() - 1)]; ChosenDialogue != nullptr)
				{
					Message.DialogueText = FText::FromString(ChosenDialogue->Dialogue);
					if(!IsPlayer)
					{
						CurrentRequest.Character.CurrentTags.AddUnique(ChosenDialogue->DialogueTag);
					}
				}
			}

			if(IsPlayer && CustomsDataMap != nullptr && CustomsDataMap->PlayerCharacter != nullptr)
			{
				Message.DialogueIcon = CustomsDataMap->PlayerCharacter->Portrait;
				FString NamesCombined;
				for(const FString& Name : CustomsDataMap->PlayerCharacter->Names)
				{
					if(!NamesCombined.IsEmpty())
					{
						NamesCombined.Append(" ");
					}
					NamesCombined.Append(Name);
				}
				Message.DisplayName = FText::FromString(NamesCombined);
			}
			else
			{
				Message.DialogueIcon = CurrentRequest.Character.Portrait;
				Message.DisplayName = FText::FromString(CurrentRequest.Character.CallSign);
			}

			Message.IsPlayer = IsPlayer;
			
			if(TimeToSend > 0.0f)
			{
				FTimerManager& TimerManager = World->GetTimerManager();
				FTimerHandle MessageHandle;
				const FTimerDelegate MessageDelegate = FTimerDelegate::CreateLambda(
					[WeakThis = TWeakObjectPtr<AAnythingToDeclareGameState>(this), Message]()
					{
						if (const AAnythingToDeclareGameState* StrongThis = WeakThis.Get())
						{
							StrongThis->SendMessage(Message);
						}
					});
				TimerManager.SetTimer(MessageHandle, MessageDelegate, TimeToSend, false);
				ConversationTimerHandles.Add(MessageHandle);
			}
			else
			{
				SendMessage(Message);
			}
		}
	}
}

void AAnythingToDeclareGameState::SendMessage(const FDialogueMessage& InMessage) const
{
	if(const UCustomsRequestConversationMonitorWidget* ConversationMonitorWidget = CachedConversationMonitorWidget.Get())
	{
		if(ConversationMonitorWidget->ConversationWidget != nullptr)
		{
			ConversationMonitorWidget->ConversationWidget->AddDialogue(InMessage.DialogueText, InMessage.DisplayName, InMessage.DialogueIcon, InMessage.IsPlayer);
		}
	}
}

void AAnythingToDeclareGameState::HandleRequest(const ECustomsRequestOutcome InOutcome)
{
	if(CurrentRequest.IsValid())
	{
		CurrentRequest.Outcome = InOutcome;
		ProcessedRequests.Add(CurrentRequest);
	}
	if(const UCustomsRequestConversationMonitorWidget* ConversationMonitorWidget = CachedConversationMonitorWidget.Get())
	{
		if(const UWorld* World = GetWorld())
		{
			FTimerManager& TimerManager = World->GetTimerManager();
			for(FTimerHandle& Handle : ConversationTimerHandles)
			{
				TimerManager.ClearTimer(Handle);
				Handle.Invalidate();
			}
			ConversationTimerHandles.Empty();
		}
		if(ConversationMonitorWidget->ConversationWidget != nullptr)
		{
			ConversationMonitorWidget->ConversationWidget->EndConversation(InOutcome);
		}
	}
	NextRequest();
}

AActor* AAnythingToDeclareGameState::CycleCameraNext()
{
	int32 CurrentCameraOrder = 0;
	AGenericConsole* ConsoleToReturn = nullptr;
	
	if(const AGenericConsole* FocusedConsolePtr = FocusedConsole.Get())
	{
		CurrentCameraOrder = FocusedConsolePtr->GetCameraOrder();
	}

	for(const TWeakObjectPtr<AGenericConsole>& Console : Consoles)
	{
		if(AGenericConsole* ConsolePtr = Console.Get())
		{
			if(CurrentCameraOrder < ConsolePtr->GetCameraOrder() && (ConsoleToReturn == nullptr
				 || ConsolePtr->GetCameraOrder() < ConsoleToReturn->GetCameraOrder()))
			{
				ConsoleToReturn = ConsolePtr;
			}
		}
	}
	if(ConsoleToReturn != nullptr && ConsoleToReturn != FocusedConsole)
	{
		FocusedConsole = ConsoleToReturn;
		// ConsolePtr->Focus();
		return ConsoleToReturn;
	}

	if(FocusedConsole.IsValid())
	{
		if(const AGenericConsole* FocusedConsolePtr = FocusedConsole.Get())
		{
			// FocusedConsolePtr->UnFocus();
		}
		FocusedConsole = nullptr;
	}
	return nullptr;
}

AActor* AAnythingToDeclareGameState::CycleCameraPrev()
{
	int32 CurrentCameraOrder = 200;
	AGenericConsole* ConsoleToReturn = nullptr;
	
	if(const AGenericConsole* FocusedConsolePtr = FocusedConsole.Get())
	{
		CurrentCameraOrder = FocusedConsolePtr->GetCameraOrder();
	}

	for(const TWeakObjectPtr<AGenericConsole>& Console : Consoles)
	{
		if(AGenericConsole* ConsolePtr = Console.Get())
		{
			if(CurrentCameraOrder > ConsolePtr->GetCameraOrder() && (ConsoleToReturn == nullptr
				 || ConsolePtr->GetCameraOrder() > ConsoleToReturn->GetCameraOrder()))
			{
				ConsoleToReturn = ConsolePtr;
			}
		}
	}
	if(ConsoleToReturn != nullptr && ConsoleToReturn != FocusedConsole)
	{
		FocusedConsole = ConsoleToReturn;
		// ConsolePtr->Focus();
		return ConsoleToReturn;
	}

	if(FocusedConsole.IsValid())
	{
		if(const AGenericConsole* FocusedConsolePtr = FocusedConsole.Get())
		{
			// FocusedConsolePtr->UnFocus();
		}
		FocusedConsole = nullptr;
	}
	return nullptr;
}

