// All Rights Reserved by SweetSpot 2025-2026.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BigEye.generated.h"

UCLASS()
class UNREALPROJECTBASE_API ABigEye : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABigEye();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	FTransform startTransform;

	UPROPERTY()
	int count = 0;

	FTimerHandle TimerHandle;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void IncreaseMadness();
	
	UFUNCTION(BlueprintCallable)
	void FadeAway();

	UFUNCTION(BlueprintCallable)
	void ResetPosition();

	UPROPERTY(EditAnywhere)
	float increaseMadnessAmount = 0.01;
};
