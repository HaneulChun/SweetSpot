// All Rights Reserved by Jason 2025-2026.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FMODEvent.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECTBASE_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
public:
	FString mvalue = "";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	UUserWidget* CurrentWidget;
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	UUserWidget* GetWidget() const;

	
	UPROPERTY(EditAnywhere, BluePrintReadWrite)
	TArray<UMaterialInterface*> Material;

	UFUNCTION(BlueprintCallable, Category = "Material")
	void SetMaterial(TArray<UMaterialInterface*> Mat);
	
	UFUNCTION(BlueprintCallable, Category = "Material")
	void ChangeCameraSettings(FPostProcessSettings& settings, float chromaticAberration, float Vignette);

	UFUNCTION(BlueprintCallable, Category = "Material")
	void Color(FPostProcessSettings& settings, float intensity);
	
	UFUNCTION(BlueprintCallable, Category = "Material")
	void ChangeCameraMaterial(float intensity);
	
	UPROPERTY()
	UFMODEvent* FullyMadSFX;
	

	UFUNCTION(BlueprintCallable)
	float GetSweatSpotValue();

	UFUNCTION(BlueprintCallable)
	float GetMadValue();

	UFUNCTION(BlueprintCallable)
	float GetCurrentValue();
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetIncreaseMadness(float value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float mmadnessBarValue = 0.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float increaseMadness = 0.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float sweatSpot = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float mad = 0;
	
	UFUNCTION()
	void IncreaseMadnessBar(float value);

	UFUNCTION(BlueprintCallable)
	TArray<float> GetCameraSettings();
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float chromaticAberrationIntensity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float vignetteIntensity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float matIntensity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float colorIntensity = 1;
	
};
