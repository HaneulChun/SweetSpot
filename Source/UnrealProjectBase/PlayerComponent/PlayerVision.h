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

	FTimerHandle TimerHandle;
	
	FTimerHandle BigTimerHandle;
	
	UPROPERTY()
	TArray<AActor*> eyeArray;
	UPROPERTY()
	TArray<UMeshComponent*> eyeMeshArray;
	UPROPERTY()
	int32 EyeIndex = 0;
	
	UPROPERTY()
	TArray<AActor*> bigEyeArray;
	UPROPERTY()
	TArray<UMeshComponent*> bigEyeMeshArray;
	UPROPERTY()
	int32 bigEyeIndex = 0;

	UPROPERTY(blueprintReadWrite)
	bool isFocusing = false;

	UPROPERTY(BlueprintReadOnly)
	UCameraComponent* PlayerCamera;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float IntensitySpeed = .5f;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

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
