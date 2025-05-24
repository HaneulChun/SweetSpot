// All Rights Reserved by Jason 2025-2026.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FMODEvent.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
class APlayerHud;
UCLASS()
class UNREALPROJECTBASE_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	FTimerHandle TimerHandle;
	bool isDying = false;
	int dyingCount = 0;

	UPROPERTY(BlueprintReadOnly)
	TArray<AActor*> SaneActors;

	UPROPERTY(BlueprintReadOnly)
	TArray<AActor*> SweetActors;
public:
	FString mvalue = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<APlayerHud> PlayerHudClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	UUserWidget* CurrentWidget;
	
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Material")
	TArray<UMaterialInterface*> Material;

	UFUNCTION(BlueprintCallable, Category = "Material")
	void SetMaterial(TArray<UMaterialInterface*> Mat);
	
	UFUNCTION(BlueprintCallable, Category = "Material")
	void ChangeCameraSettings(float chromaticAberration, float Vignette);

	UFUNCTION(BlueprintCallable, Category = "Material")
	void Color(float intensity);
	
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

	UFUNCTION(BlueprintCallable, Category = "UI")
	void DecreaseMadness(float value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float currentMadnessBarValue = 0.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float increaseMadness = 0.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float sweatSpot = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float mad = 0;
	
	UFUNCTION(BlueprintCallable)
	void IncreaseMadnessBar(float value);
	

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Fade(float saneTime, float saneStartValue, float sweetTime, float sweetStartValue);
	virtual void Fade_Implementation(float saneTime, float saneStartValue, float sweetTime, float sweetStartValue);

	
	UFUNCTION(BlueprintCallable)
	void Dying();

	UFUNCTION(BlueprintCallable)
	void Dead();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float chromaticAberrationIntensity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float vignetteIntensity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float matIntensity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float colorIntensity = 1;


	UPROPERTY()
	bool isInRoom = false;
};
