// All Rights Reserved by Jason 2025-2026.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FMODEvent.h"
#include "MyUserWidget.generated.h"

class UCameraComponent;
/**
 * 
 */
UENUM(BlueprintType)
enum class ECurrentState : uint8
{
	Sane       UMETA(DisplayName = "Sane"),
	SweetSpot  UMETA(DisplayName = "Sweet Spot"),
	Mad        UMETA(DisplayName = "Mad"),
	Dead       UMETA(DisplayName = "Dead")
};


class APlayerHud;
UCLASS()
class UNREALPROJECTBASE_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	// cache
	FTimerHandle TimerHandle;
	bool isDying = false;
	int dyingCount = 0;

	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<AActor>> SaneActors;

	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<AActor>> SweetActors;

	UPROPERTY()
	TObjectPtr<AActor> spawnPoint;

	UPROPERTY()
	TObjectPtr<UCameraComponent> playerCamera;

	UPROPERTY()
	TObjectPtr<APawn> Player;

	
	UPROPERTY()
	TSoftObjectPtr<UWorld> checkUnloadedLevel;
public:
	UPROPERTY(BlueprintReadOnly)
	ECurrentState CurrentState = ECurrentState::SweetSpot;


	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<APlayerHud> playerHud;
	
	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UUserWidget> CurrentWidget;

	
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Material")
	TArray<TObjectPtr<UMaterialInterface>> Material;

	UFUNCTION(BlueprintCallable, Category = "Material")
	void SetMaterial(TArray<UMaterialInterface*> Mat);
	
	UFUNCTION(BlueprintCallable, Category = "Material")
	void ChangeCameraSettings(float chromaticAberration, float Vignette);

	UFUNCTION(BlueprintCallable, Category = "Material")
	void Color(float intensity);
	
	UFUNCTION(BlueprintCallable, Category = "Material")
	void ChangeCameraMaterial(float intensity);


	UFUNCTION(BlueprintCallable)
	void CheckForSubLevel(TSoftObjectPtr<UWorld> unloadedSubLevel);

	FTimerHandle TimerHandleLevel;
	
	UPROPERTY()
	TObjectPtr<UFMODEvent> FullyMadSFX;
	

	UFUNCTION(BlueprintCallable)
	float GetSweetSpotValue();

	UFUNCTION(BlueprintCallable)
	float GetMadValue();

	UFUNCTION(BlueprintCallable)
	float GetCurrentValue();
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetIncreaseMadness(float value);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void DecreaseMadness(float value);
	
	UFUNCTION(BlueprintCallable)
	void IncreaseMadnessBar(float value);
	

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Fade(float saneTime, float saneStartValue, float sweetTime, float sweetStartValue);
	virtual void Fade_Implementation(float saneTime, float saneStartValue, float sweetTime, float sweetStartValue);

	
	UFUNCTION(BlueprintCallable)
	void Dying();

	UFUNCTION(BlueprintCallable)
	void Dead();

	UFUNCTION(BlueprintCallable)
	void StartLoop();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float chromaticAberrationIntensity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float vignetteIntensity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float matIntensity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float colorIntensity = 1;

	// value roomMadnessDamage
	UPROPERTY()
	float roomMadnessDamage = 0;

	UPROPERTY()
	bool isInRoom = false;

	UPROPERTY()
	bool isInLight = false;
	
	UPROPERTY(BlueprintReadWrite)
	bool isImmune = false;


	// property
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float currentMadnessBarValue = 0.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float increaseMadness = 0.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float sweetSpot = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float mad = 0;
};
