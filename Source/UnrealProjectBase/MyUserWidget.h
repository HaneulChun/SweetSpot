// All Rights Reserved by Jason 2025-2026.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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

	FString mvalue = "";
	
public:
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
	void ChangeCameraMaterial(FPostProcessSettings& settings, float intensity);
	
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetIncreaseMadness(float value);

	UPROPERTY(EditAnywhere, BluePrintReadWrite)
	float mmadnessBarValue = 0.0;

	UPROPERTY(EditAnywhere, BluePrintReadWrite)
	float increaseMadness = 0.0;

	UPROPERTY(EditAnywhere, BluePrintReadWrite)
	float sweatSpot = 0;

	UPROPERTY(EditAnywhere, BluePrintReadWrite)
	float mad = 0;

	UFUNCTION()
	void IncreaseMadnessBar(float value);
};
