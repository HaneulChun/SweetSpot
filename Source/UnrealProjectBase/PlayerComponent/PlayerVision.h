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
	FTimerHandle TimerHandle;
	FTimerHandle BigTimerHandle;

	// property for tentical 
	UPROPERTY()
	TArray<TObjectPtr<AActor>> tenticalArray;
	UPROPERTY()
	TArray<TObjectPtr<UMeshComponent>> tenticalMeshArray;
	UPROPERTY()
	int32 tenticalIndex = 0;

	// property for eye 
	UPROPERTY()
	TArray<TObjectPtr<AActor>> eyeArray;
	UPROPERTY()
	TArray<TObjectPtr<UMeshComponent>> eyeMeshArray;
	UPROPERTY()
	int32 EyeIndex = 0;

	// property for big eye 
	UPROPERTY()
	TArray<TObjectPtr<AActor>> bigEyeArray;
	UPROPERTY()
	TArray<TObjectPtr<UMeshComponent>> bigEyeMeshArray;
	UPROPERTY()
	int32 bigEyeIndex = 0;

	UPROPERTY(blueprintReadWrite)
	bool isFocusing = false;

	UPROPERTY(BlueprintReadOnly)
	UCameraComponent* PlayerCamera;


	// Interval for checking object
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float tenticalCheckInterval = .1f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float eyeCheckInterval = .1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float bigEyeCheckInterval = .1f;

	
	UFUNCTION()
	float DotProduct(FVector TargetVector);
public:	

	UFUNCTION()
	void LookForTenticalWall();
	
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
};
