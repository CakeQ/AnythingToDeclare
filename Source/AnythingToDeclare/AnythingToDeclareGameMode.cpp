// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#include "AnythingToDeclareGameMode.h"

#include "AnythingToDeclareGameState.h"
#include "AnythingToDeclarePlayerController.h"
#include "AnythingToDeclarePawn.h"

#include "Kismet/GameplayStatics.h"

AAnythingToDeclareGameMode::AAnythingToDeclareGameMode(const FObjectInitializer& InInitializer)
	: Super(InInitializer)
{
	DefaultPawnClass = AAnythingToDeclarePawn::StaticClass();
	PlayerControllerClass = AAnythingToDeclarePlayerController::StaticClass();
	GameStateClass = AAnythingToDeclareGameState::StaticClass();
}
