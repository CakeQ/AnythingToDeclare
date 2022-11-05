// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/


#include "GenericConsole.h"


AGenericConsole::AGenericConsole(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, BaseMesh(ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("BaseMesh")))
	, ScreenWidget(ObjectInitializer.CreateDefaultSubobject<UWidgetComponent>(this, TEXT("ScreenWidget")))
	, SpringArmComponent(ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("SpringArm")))
	, CameraComponent(ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("Camera")))
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(BaseMesh);
	ScreenWidget->SetupAttachment(GetRootComponent());
	SpringArmComponent->SetupAttachment(GetRootComponent());
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void AGenericConsole::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGenericConsole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

