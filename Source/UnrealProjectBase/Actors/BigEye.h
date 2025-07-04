// All Rights Reserved by SweetSpot 2025-2026.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BigEye.generated.h"

class UMyUserWidget;
UCLASS()
class UNREALPROJECTBASE_API ABigEye : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABigEye();

	UPROPERTY(BlueprintReadOnly)
	int count = 0;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<UMyUserWidget> MadnessWidget;
	
	FTransform startTransform;

	FTimerHandle TimerHandle;
	FTimerHandle TimerHandleImmune;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float restoreMadnessValue = 0.1;
public:	

	UFUNCTION()
	void IncreaseMadness();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void FadeAway();
	virtual void FadeAway_Implementation();

	UFUNCTION(BlueprintImplementableEvent , BlueprintCallable)
	void LookAtPlayer();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ResetPosition();
	virtual void ResetPosition_Implementation();

	UFUNCTION(BlueprintCallable)
	void RemoveImmunity();

	UPROPERTY(EditAnywhere)
	float PushBackForce = .5f;

	UPROPERTY(EditAnywhere)
	float radius = 0.95f;
	
	UPROPERTY(EditAnywhere)
	float increaseMadnessAmount = 0.01;

	UPROPERTY(EditAnywhere)
	float immunityTime = 10;

	UPROPERTY(EditAnywhere)
	int focusedLookTicks = 20;
};
