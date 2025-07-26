// All Rights Reserved by SweetSpot 2025-2026.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CameraSettingsComponent.generated.h"


class UCameraComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class UNREALPROJECTBASE_API UCameraSettingsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCameraSettingsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<UMaterialInterface>> Material;
	
	UPROPERTY()
	TObjectPtr<UCameraComponent> playerCamera;

	UFUNCTION(BlueprintCallable)
	void RoomColor(float intensity, float Vignette, float FieldOfView);
	
	UPROPERTY(EditAnywhere)
	float duration = .5f;
	UPROPERTY()
	float ElapsedTime = 0.0f;
	
	UPROPERTY(BlueprintReadOnly)
	float startColor = 1.0f;
	UPROPERTY()
	float endColor = 0.0f;

	UPROPERTY()
	float startVignette = 1.0f;
	UPROPERTY()
	float endVignette = 0.0f;

	UPROPERTY()
	float startFOV = 1.0f;
	UPROPERTY()
	float endFOV = 0.0f;
public:

	UFUNCTION()
	void ChangeCameraSettings(float chromaticAberration, float Vignette);
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetCameraSettings(float intensity, float Vignette, float FieldOfView);

	UFUNCTION(BlueprintCallable)
	void Color(float intensity);

	UFUNCTION(BlueprintCallable)
	void ChangeCameraMaterial(float intensity);

	UFUNCTION(BlueprintImplementableEvent)
	void DelayrestoreCamera();
};
