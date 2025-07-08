// All Rights Reserved by Jason 2025-2026.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerVision.generated.h"


class UCameraComponent;
class UMeshComponent;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPROJECTBASE_API UPlayerVision : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerVision();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	// timer 
	FTimerHandle tenticalTimerHandle;

	// property for tentical 
	TArray<TObjectPtr<AActor>> tenticalArray;

	// property for eye 
	TArray<TObjectPtr<AActor>> eyeArray;
	TArray<TObjectPtr<UMeshComponent>> eyeMeshArray;
	int32 EyeIndex = 0;

	// property for big eye 
	TArray<TObjectPtr<AActor>> bigEyeArray;
	TArray<TObjectPtr<UMeshComponent>> bigEyeMeshArray;
	int32 bigEyeIndex = 0;

	UPROPERTY(blueprintReadWrite)
	bool isFocusing = false;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UCameraComponent> PlayerCamera;

	
	UFUNCTION()
	float DotProduct(const FVector &TargetVector);

	UPROPERTY()
	float height = 105;
	
public:	

	UFUNCTION()
	void Interval();
	
	UFUNCTION()
	void LookForTentacleWall();
	
	UFUNCTION()
	void LookForEye();

	UFUNCTION()
	void LookForBigEye();
	
	UFUNCTION(BlueprintCallable)
	void SetActorArray();

	
	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY()
	TObjectPtr<APawn> PlayerPawn;

	FVector PlayerLocation;
	
	// Interval for checking object
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float tenticalCheckInterval = .1f;

	UPROPERTY(EditAnywhere)
	float distance = 1000.0f;
};
