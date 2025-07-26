// All Rights Reserved by SweetSpot 2025-2026.


#include "CameraSettingsComponent.h"

#include "Camera/CameraComponent.h"

// Sets default values for this component's properties
UCameraSettingsComponent::UCameraSettingsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCameraSettingsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (TObjectPtr<APlayerController> PlayerController = GetWorld()->GetFirstPlayerController())
	{
		// point at the player's camera
		if (TObjectPtr<UCameraComponent> Camera = PlayerController->PlayerCameraManager->GetOwningPlayerController()->PlayerCameraManager->ViewTarget.Target->FindComponentByClass<UCameraComponent>())
		{
			playerCamera = Camera;
		}	
	}
	SetComponentTickEnabled(false);
}


// Called every frame
void UCameraSettingsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (ElapsedTime < duration)
	{
		ElapsedTime += DeltaTime;
		float Alpha = FMath::Clamp(ElapsedTime / duration, 0.0f, 1.0f);
		float newColor = FMath::Lerp(startColor, endColor, Alpha);
		float newVignette = FMath::Lerp(startVignette, endVignette, Alpha);
		float newFOV = FMath::Lerp(startFOV, endFOV, Alpha);
		RoomColor(newColor, newVignette, newFOV);
	}
	else
	{
		SetComponentTickEnabled(false);
	}
}

void UCameraSettingsComponent::SetCameraSettings(float intensity, float Vignette, float FieldOfView)
{
	// set up for tick
	ElapsedTime = 0.0f;
	
	startColor = playerCamera->PostProcessSettings.ColorSaturation.X;
	startVignette = playerCamera->PostProcessSettings.VignetteIntensity;
	startFOV = playerCamera->FieldOfView;
	
	endColor = intensity;
	endVignette = Vignette;
	endFOV = FieldOfView;

	if (intensity < 0)
	{
		endColor = playerCamera->PostProcessSettings.ColorSaturation.X;
	}
	if (Vignette < 0)
	{
		endVignette = playerCamera->PostProcessSettings.VignetteIntensity;
	}
	SetComponentTickEnabled(true);
}

void UCameraSettingsComponent::ChangeCameraSettings(float chromaticAberration, float Vignette)
{
	FPostProcessSettings& Settings = playerCamera->PostProcessSettings;

	Settings.bOverride_SceneFringeIntensity = true;
	Settings.SceneFringeIntensity = chromaticAberration;

	Settings.bOverride_VignetteIntensity = true;
	Settings.VignetteIntensity = Vignette;
}

void UCameraSettingsComponent::Color(float intensity)
{
	FPostProcessSettings& Settings = playerCamera->PostProcessSettings;
			
	Settings.bOverride_ColorSaturation = true;
	Settings.ColorSaturation = FVector4(intensity, intensity, intensity, 1.0f);
}

void UCameraSettingsComponent::ChangeCameraMaterial(float intensity)
{
	FPostProcessSettings& Settings = playerCamera->PostProcessSettings;

	for (int32 i = 0; i < Material.Num(); i++)
	{
		if (Material.IsValidIndex(i))
		{
			Settings.AddBlendable(Material[i], intensity);
		}
	}
}

void UCameraSettingsComponent::RoomColor(float intensity, float Vignette, float FieldOfView)
{
	FPostProcessSettings& Settings = playerCamera->PostProcessSettings;

	if (intensity <= 1)
	{
		Settings.bOverride_ColorSaturation = true;
		Settings.ColorSaturation = FVector4(intensity, intensity, intensity, 1.0f);

		Settings.bOverride_VignetteIntensity = true;
		Settings.VignetteIntensity = Vignette;	
	}
	else
	{
		Settings.bOverride_ColorSaturation = true;
		Settings.ColorSaturation = FVector4(intensity, intensity/2, intensity, 1.0f);
	}
	playerCamera->SetFieldOfView(FieldOfView);
}

