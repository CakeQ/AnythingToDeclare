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
	
private:
	UPROPERTY(EditAnywhere)
	int32 CameraOrder;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMesh;
	
	UPROPERTY(EditAnywhere)
	UWidgetComponent* ScreenWidget;
	
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComponent;
};
