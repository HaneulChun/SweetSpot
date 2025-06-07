// All Rights Reserved by SweetSpot 2025-2026.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TentacleWall.generated.h"

class UMyUserWidget;
class UBoxComponent;

UCLASS()
class UNREALPROJECTBASE_API ATentacleWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATentacleWall();
	
private:
	UPROPERTY()
	float finalLocation;

	UPROPERTY()
	float startLocation;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle TimerHandle;

	UPROPERTY()
	bool isPlayerNear = false;
	
	UPROPERTY()
	TObjectPtr<UMyUserWidget> widget;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> triggerBox;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
					  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION()
	void IncreaseMadnessBar();

	
	UPROPERTY()
	FTransform startTransform;

	UPROPERTY()
	int count = 0;
public:	

	UFUNCTION(BlueprintCallable)
	void FadeAway();

	UFUNCTION(BlueprintCallable)
	void Spawn();

	UFUNCTION(BlueprintCallable)
	void StartDown();

	UFUNCTION()
	void ResetPosition();

	UFUNCTION(BlueprintImplementableEvent)
	void DestroyTentacle();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float IncreaseMadness = 0.02f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MadnessTickInterval = 0.4f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float speed = 9.0f;
	
	UPROPERTY(BlueprintReadWrite)
	bool isFading = false;

	UPROPERTY(BlueprintReadWrite)
	bool isSpawning = false;
	
	
	UPROPERTY(EditAnywhere)
	int focusedLookTicks = 20;
};
