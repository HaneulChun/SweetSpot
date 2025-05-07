// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MadnessMeterWidget.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EMadnessState : uint8
{
	Sane UMETA(DisplayName = "Sane"),
	Mad UMETA(DisplayName = "Mad"),
	SweatSpot UMETA(DisplayName = "Sweat Spot")
};

UCLASS()
class UNREALPROJECTBASE_API UMadnessMeterWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Madness")
	EMadnessState CurrentState = EMadnessState::Sane;

public:
	// Visual change 
	UPROPERTY(EditAnywhere, BluePrintReadWrite)
	TArray<UMaterialInterface*> Material;

	UFUNCTION(BlueprintCallable, Category = "Material")
	void SetMaterial(TArray<UMaterialInterface*> Mat);

	UFUNCTION(BlueprintCallable, Category = "Material")
	void ChangeCameraSettings(float chromaticAberration, float Vignette);

	UFUNCTION(BlueprintCallable, Category = "Material")
	void ChangeCameraMaterial(float intensity);


	// Madness Bar
	UFUNCTION()
	void IncreaseMadnessBar(float value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float currentMadnessValue = 0;

	UPROPERTY()
	float sweatSpot = 0;

	UPROPERTY()
	float mad = 0;
};
