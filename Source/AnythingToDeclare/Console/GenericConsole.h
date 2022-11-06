// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/SpringArmComponent.h"
#include "GenericConsole.generated.h"

UCLASS()
class ANYTHINGTODECLARE_API AGenericConsole : public AActor
{
	GENERATED_BODY()

public:
	AGenericConsole(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	int32 GetCameraOrder() const { return CameraOrder; };
	
	UCameraComponent* GetConsoleCamera() const { return CameraComponent; };
	UWidgetComponent* GetScreenWidget() const { return ScreenWidget; };
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CameraOrder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* BaseMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetComponent* ScreenWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* CameraComponent;
};
