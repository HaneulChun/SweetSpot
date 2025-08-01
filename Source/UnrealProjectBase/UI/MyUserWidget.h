// All Rights Reserved by Jason 2025-2026.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FMODEvent.h"
#include "MyUserWidget.generated.h"

class UCameraSettingsComponent;
class UFadeObjectComponent;
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
	
	// cache
	FTimerHandle TimerHandle;
	int dyingCount = 0;
	
	UPROPERTY()
	TObjectPtr<APawn> Player;

	UPROPERTY()
	TObjectPtr<UCameraSettingsComponent> CameraSettings;

public:
	UPROPERTY(BlueprintReadOnly)
	ECurrentState CurrentState = ECurrentState::SweetSpot;
	
	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<APlayerHud> playerHud;
	
	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UUserWidget> CurrentWidget;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UFadeObjectComponent> FadeObject;
	
	UPROPERTY(BlueprintReadWrite, Category = "UI")
	FTimerHandle TimerHandleLevel;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	TObjectPtr<UFMODEvent> FullyMadSFX;
	
	UFUNCTION(BlueprintCallable)
	void CheckPlayerState();
	
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

	UFUNCTION(BlueprintImplementableEvent , BlueprintCallable)
	void UnFocus();
	
	UFUNCTION(BlueprintCallable)
	void Dead();

	UFUNCTION(BlueprintCallable)
	void SpawnPlayer();
	
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
	bool hasKey = false;
	
	
	UFUNCTION(BlueprintImplementableEvent , BlueprintCallable)
	void ChangedPlayerState();
	
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