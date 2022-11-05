// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#include "AnythingToDeclarePawn.h"
#include "AnythingToDeclareBlock.h"
#include "AnythingToDeclareGameState.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

AAnythingToDeclarePawn::AAnythingToDeclarePawn(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AAnythingToDeclarePawn::BeginPlay()
{
	Super::BeginPlay();
	if(UWorld* World = GetWorld())
	{
		if(AGameStateBase* GameStateBase = World->GetGameState())
		{
			if(AAnythingToDeclareGameState* GameState = Cast<AAnythingToDeclareGameState>(GameStateBase))
			{
				CachedGameState = GameState;
			}
		}
	}
}

void AAnythingToDeclarePawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AAnythingToDeclarePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("TriggerClick", EInputEvent::IE_Pressed, this, &AAnythingToDeclarePawn::TriggerClick);
	PlayerInputComponent->BindAction("CycleCameraNext", EInputEvent::IE_Pressed, this, &AAnythingToDeclarePawn::CycleCameraNext);
	PlayerInputComponent->BindAction("CycleCameraPrev", EInputEvent::IE_Pressed, this, &AAnythingToDeclarePawn::CycleCameraPrev);
}

void AAnythingToDeclarePawn::CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult)
{
	Super::CalcCamera(DeltaTime, OutResult);

	OutResult.Rotation = FRotator(-90.0f, -90.0f, 0.0f);
}

void AAnythingToDeclarePawn::TriggerClick()
{
}

void AAnythingToDeclarePawn::CycleCameraNext()
{
	if(AAnythingToDeclareGameState* GameState = CachedGameState.Get())
	{
		if(AActor* NextCameraActor = GameState->CycleCameraNext())
		{
			if(APlayerController* PlayerController = Cast<APlayerController>(Controller))
			{
				PlayerController->SetViewTargetWithBlend(NextCameraActor, 1.0f, VTBlend_EaseOut);
			}
		}
	}
}

void AAnythingToDeclarePawn::CycleCameraPrev()
{
	if(AAnythingToDeclareGameState* GameState = CachedGameState.Get())
	{
		if(AActor* PrevCameraActor = GameState->CycleCameraPrev())
		{
			if(APlayerController* PlayerController = Cast<APlayerController>(Controller))
			{
				PlayerController->SetViewTargetWithBlend(PrevCameraActor, 1.0f, VTBlend_EaseOut);
			}
		}
	}
}
