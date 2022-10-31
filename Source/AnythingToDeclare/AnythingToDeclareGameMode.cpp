// Copyright Epic Games, Inc. All Rights Reserved.

#include "AnythingToDeclareGameMode.h"
#include "AnythingToDeclarePlayerController.h"
#include "AnythingToDeclarePawn.h"

AAnythingToDeclareGameMode::AAnythingToDeclareGameMode()
{
	// no pawn by default
	DefaultPawnClass = AAnythingToDeclarePawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = AAnythingToDeclarePlayerController::StaticClass();
}
