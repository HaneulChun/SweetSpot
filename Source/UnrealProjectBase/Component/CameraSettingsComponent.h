// All Rights Reserved by SweetSpot 2025-2026.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CameraSettingsComponent.generated.h"


class UCameraComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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
	
	TObjectPtr<UCameraComponent> playerCamera;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ChangeCameraSettings(float chromaticAberration, float Vignette);

	UFUNCTION(BlueprintCallable)
	void Color(float intensity);

	UFUNCTION(BlueprintCallable)
	void ChangeCameraMaterial(float intensity);
};
