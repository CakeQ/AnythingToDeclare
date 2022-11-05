// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#include "AnythingToDeclarePawn.h"
#include "AnythingToDeclareGameState.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

AAnythingToDeclarePawn::AAnythingToDeclarePawn(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
	, CameraCycleBlendTime(1.0f)
	, CameraCycleBlendType(VTBlend_EaseOut)
	, BaseComponent(ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("BaseComponent")))
	, SpringArmComponent(ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("SpringArmComponent")))
	, CameraComponent(ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("CameraComponent")))
{
	SetRootComponent(BaseComponent);
	SpringArmComponent->SetupAttachment(BaseComponent);
	CameraComponent->SetupAttachment(SpringArmComponent);
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

void AAnythingToDeclarePawn::TriggerClick()
{
}

void AAnythingToDeclarePawn::CycleCameraNext()
{
	if(AAnythingToDeclareGameState* GameState = CachedGameState.Get())
	{
		if(APlayerController* PlayerController = Cast<APlayerController>(Controller))
		{
			if(AActor* NextCameraActor = GameState->CycleCameraNext())
			{
				PlayerController->SetViewTargetWithBlend(NextCameraActor, CameraCycleBlendTime, CameraCycleBlendType, CameraCycleBlendExp);
			}
			else
			{
				PlayerController->SetViewTargetWithBlend(this, CameraCycleBlendTime, CameraCycleBlendType, CameraCycleBlendExp);
			}
		}
	}
}

void AAnythingToDeclarePawn::CycleCameraPrev()
{
	if(AAnythingToDeclareGameState* GameState = CachedGameState.Get())
	{
		if(APlayerController* PlayerController = Cast<APlayerController>(Controller))
		{
			if(AActor* PrevCameraActor = GameState->CycleCameraPrev())
			{
				PlayerController->SetViewTargetWithBlend(PrevCameraActor, CameraCycleBlendTime, CameraCycleBlendType, CameraCycleBlendExp);
			}
			else
			{
				PlayerController->SetViewTargetWithBlend(this, CameraCycleBlendTime, CameraCycleBlendType, CameraCycleBlendExp);
			}
		}
	}
}
