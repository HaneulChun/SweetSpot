// All Rights Reserved by SweetSpot 2025-2026.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TentacleWall.generated.h"

class ASweetSpotCharacter;
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
	FVector finalLocation;

	FVector startLocation;
	
	float currentAlpha = 0;

	UPROPERTY()
	TObjectPtr<ASweetSpotCharacter> Character;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
	FTimerHandle TimerHandle;
	
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float slowPlayer = 200;

	float OriginalSpeed;
public:	
	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> MovingSceneComponent;
	
	UFUNCTION(BlueprintCallable)
	void FadeAway();

	UFUNCTION(BlueprintCallable)
	void Spawn();

	UFUNCTION(BlueprintCallable)
	void StartDown();

	
	UFUNCTION(BlueprintImplementableEvent)
	void CameraShake();
	
	UFUNCTION(BlueprintNativeEvent)
	void ResetTentaclePosition();
	virtual void ResetTentaclePosition_Implementation();
	
	
	UFUNCTION(BlueprintImplementableEvent)
	void DestroyTentacle();

	
	UPROPERTY(BlueprintReadWrite)
	bool isActive = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float restoreMadnessValue = 0.1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float IncreaseMadness = 0.02f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MadnessTickInterval = 0.4f;

	UPROPERTY()
	float speed = 9.0f;
	
	UPROPERTY(EditAnywhere)
	int focusedLookTicks = 20;

	UPROPERTY(BlueprintReadOnly)
	int count = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float comingUpSpeed = 2;
};
