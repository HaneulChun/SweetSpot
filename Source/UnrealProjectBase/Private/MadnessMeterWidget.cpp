// Fill out your copyright notice in the Description page of Project Settings.


#include "MadnessMeterWidget.h"
#include "Camera/CameraComponent.h"

void UMadnessMeterWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMadnessMeterWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	currentMadnessValue += 0.001;
	
	if (currentMadnessValue <= sweatSpot) // sane
	{
		ChangeCameraSettings(0, 0.4f);
		ChangeCameraMaterial(0.0f);
		
		CurrentState = EMadnessState::Sane;
	}
	else if (currentMadnessValue >= 1) // dead
	{
		currentMadnessValue = 0;
	}
	else if (currentMadnessValue >= mad) // mads
	{
		if (CurrentState != EMadnessState::Mad)
		{
			ChangeCameraSettings(5, 1);
			ChangeCameraMaterial(0.0f);
			
			CurrentState = EMadnessState::Mad;
		}
	}
	else // sweat spot
	{
		if (CurrentState != EMadnessState::SweatSpot)
		{
			ChangeCameraSettings(0, 0.4f);
			ChangeCameraMaterial(1.0f);
			
			CurrentState = EMadnessState::SweatSpot;
		}
	}
}

// initialize materials
void UMadnessMeterWidget::SetMaterial(TArray<UMaterialInterface*> Mat)
{
	Material = Mat;
}

void UMadnessMeterWidget::ChangeCameraSettings(float chromaticAberration, float Vignette)
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		// point at the player's camera
		if (UCameraComponent* Camera = PlayerController->PlayerCameraManager->GetOwningPlayerController()->PlayerCameraManager->ViewTarget.Target->FindComponentByClass<UCameraComponent>())
		{
			FPostProcessSettings& Settings = Camera->PostProcessSettings;
					
			Settings.bOverride_SceneFringeIntensity = true;
			Settings.SceneFringeIntensity = chromaticAberration;

			Settings.bOverride_VignetteIntensity = true;
			Settings.VignetteIntensity = Vignette;
		}
	}
}

void UMadnessMeterWidget::ChangeCameraMaterial(float intensity)
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		// point at the player's camera
		if (UCameraComponent* Camera = PlayerController->PlayerCameraManager->GetOwningPlayerController()->PlayerCameraManager->ViewTarget.Target->FindComponentByClass<UCameraComponent>())
		{
			FPostProcessSettings& Settings = Camera->PostProcessSettings;

			for (int32 i = 0; i < Material.Num(); i++)
			{
				if (Material.IsValidIndex(i))
				{
					Settings.AddBlendable(Material[i], intensity);
				}
			}
		}
	}
}

void UMadnessMeterWidget::IncreaseMadnessBar(float value)
{
	currentMadnessValue += value;
}
