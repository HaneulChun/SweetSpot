// All Rights Reserved by SweetSpot 2025-2026.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SweetSpotCharacter.generated.h"

UCLASS()
class UNREALPROJECTBASE_API ASweetSpotCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASweetSpotCharacter();

protected:
	UPROPERTY(BlueprintReadWrite)
	float cameraTilt = 0;

	UFUNCTION(BlueprintCallable)
	bool IsEditor();
public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintImplementableEvent)
	void DeathCameraMovement();
	
	UFUNCTION(BlueprintImplementableEvent)
	void Dead();
};
