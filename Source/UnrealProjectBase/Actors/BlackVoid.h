// All Rights Reserved by SweetSpot 2025-2026.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlackVoid.generated.h"

UENUM(BlueprintType)
enum class EDistance : uint8
{
	veryClose       UMETA(DisplayName = "very Close"),
	close  UMETA(DisplayName = "close"),
	far        UMETA(DisplayName = "far"),
};

class UCameraSettingsComponent;
class ASweetSpotCharacter;
class UBoxComponent;

UCLASS()
class UNREALPROJECTBASE_API ABlackVoid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlackVoid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> start;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> end;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> blackVoid;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	TObjectPtr<UBoxComponent> triggerBox;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> moveingComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<ASweetSpotCharacter> player;

	UPROPERTY()
	TObjectPtr<UCameraSettingsComponent> CameraSettings;

	UPROPERTY(BlueprintReadOnly)
	EDistance DistanceState = EDistance::veryClose;
public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void StartVoid();

	UFUNCTION(BlueprintImplementableEvent)
	void PlaySound();
private:
	UPROPERTY(EditAnywhere)
	float MoveDuration = 4.0f;

	UPROPERTY()
	float ElapsedTime = 0.0f;
};
