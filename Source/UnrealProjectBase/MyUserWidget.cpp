// All Rights Reserved by Sweet Spot 2025-2026.

#include "MyUserWidget.h"

#include "EngineUtils.h"
#include "Camera/CameraComponent.h"
#include "Engine/Scene.h"

void UMyUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	bIsFocusable = true;

	if (WidgetClass)
	{
		CurrentWidget = CreateWidget<UUserWidget>(this, WidgetClass);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

void UMyUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if(mmadnessBarValue <= sweatSpot) // sane 
	{
		if (mvalue != "sane")
		{
			// get the reference of the cameras settings 
			if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
			{
				// point at the player's camera
				if (UCameraComponent* Camera = PlayerController->PlayerCameraManager->GetOwningPlayerController()->PlayerCameraManager->ViewTarget.Target->FindComponentByClass<UCameraComponent>())
				{
					FPostProcessSettings& Settings = Camera->PostProcessSettings;
					
					ChangeCameraSettings(Settings, 0.0, 0.4);
					ChangeCameraMaterial(Settings, 0.0f);
				}
			}
			mvalue = "sane";
		}
	}
	else if(mmadnessBarValue >= 1) // dead 
	{
		// find object with spawn tag and teleport to spawn
		if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
		{
			if (APawn* Player = PlayerController->GetPawn())
			{
				for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
				{
					AActor* Actor = *ActorItr;
		
					if (Actor->Tags.Contains("Spawn"))
					{
						Player->SetActorLocation(Actor->GetActorLocation());
					}
				}
			}

			mmadnessBarValue = 0;
			// point at the player's camera
			if (UCameraComponent* Camera = PlayerController->PlayerCameraManager->GetOwningPlayerController()->PlayerCameraManager->ViewTarget.Target->FindComponentByClass<UCameraComponent>())
			{
				FPostProcessSettings& Settings = Camera->PostProcessSettings;
				
				ChangeCameraSettings(Settings, 0.0, 0.4);
				ChangeCameraMaterial(Settings, 0.0f);
			}
		}
	}
	else if(mmadnessBarValue >= mad) // mad
	{
		if (mvalue != "mad")
		{
			if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
			{
				// point at the player's camera
				if (UCameraComponent* Camera = PlayerController->PlayerCameraManager->GetOwningPlayerController()->PlayerCameraManager->ViewTarget.Target->FindComponentByClass<UCameraComponent>())
				{
					FPostProcessSettings& Settings = Camera->PostProcessSettings;
					
					FTimerDelegate TimerDelegate;
					TimerDelegate.BindLambda([&]
					{
						ChangeCameraSettings(Settings, 5.0, 1.0);
						ChangeCameraMaterial(Settings, 0.0f);
					});
					
					ChangeCameraSettings(Settings, 5.0, 1.0);
					ChangeCameraMaterial(Settings, 0.0f);

					FTimerHandle TimerHandle;
					GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 3, false);
				}
			}
			mvalue = "mad";
		}
	}
	else // sweat spot
	{
		if (mvalue != "sweat")
		{
			if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
			{
				// point at the player's camera
				if (UCameraComponent* Camera = PlayerController->PlayerCameraManager->GetOwningPlayerController()->PlayerCameraManager->ViewTarget.Target->FindComponentByClass<UCameraComponent>())
				{
					FPostProcessSettings& Settings = Camera->PostProcessSettings;
					
					ChangeCameraSettings(Settings, 0.0, 0.4);
					ChangeCameraMaterial(Settings, 1.0f);
				}
			}
			mvalue = "sweat";
		}
	}
}

UUserWidget* UMyUserWidget::GetWidget() const
{
	return CurrentWidget;
}

void UMyUserWidget::SetMaterial(TArray<UMaterialInterface*> Mat)
{
	Material = Mat;
}

void UMyUserWidget::ChangeCameraSettings(FPostProcessSettings& settings, float chromaticAberration, float Vignette)
{
	FPostProcessSettings& Settings = settings;
	
	Settings.bOverride_SceneFringeIntensity = true;
	Settings.SceneFringeIntensity = chromaticAberration;

	Settings.bOverride_VignetteIntensity = true;
	Settings.VignetteIntensity = Vignette;
}

void UMyUserWidget::ChangeCameraMaterial(FPostProcessSettings& settings, float intensity)
{
	FPostProcessSettings& Settings = settings;

	for (int32 i = 0; i < Material.Num(); i++)
	{
		if (Material.IsValidIndex(i))
		{
			Settings.AddBlendable(Material[i], intensity);
		}
	}
}

void UMyUserWidget::SetIncreaseMadness(float value)
{
	increaseMadness = value;
}

void UMyUserWidget::IncreaseMadnessBar(float value)
{
	mmadnessBarValue += value;
}
