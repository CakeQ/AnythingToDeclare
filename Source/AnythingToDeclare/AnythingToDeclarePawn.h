// Copyright Daniel Thompson and Archie Whitehead @ https://github.com/CakeQ/

#pragma once

#include "CoreMinimal.h"
#include "AnythingToDeclareGameMode.h"
#include "AnythingToDeclareGameState.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Pawn.h"
#include "AnythingToDeclarePawn.generated.h"

UCLASS(config=Game)
class AAnythingToDeclarePawn : public APawn
{
	GENERATED_UCLASS_BODY()

protected:
	virtual void BeginPlay() override;
	
public:

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	void TriggerClick();
	
	void CycleCameraNext();
	void CycleCameraPrev();

	UPROPERTY(EditDefaultsOnly)
	float CameraCycleBlendTime;

	UPROPERTY(EditDefaultsOnly)
	float CameraCycleBlendExp;

	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<EViewTargetBlendFunction> CameraCycleBlendType;
	
	UPROPERTY()
	TWeakObjectPtr<AAnythingToDeclareGameState> CachedGameState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	USphereComponent* BaseComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArmComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	UCameraComponent* CameraComponent;
};
