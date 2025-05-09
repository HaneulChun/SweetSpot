// All Rights Reserved by Sweet Spot 2025-2026.

#include "MyUserWidget.h"

#include "EngineUtils.h"
#include "Camera/CameraComponent.h"
#include "Engine/Scene.h"
#include "FMODBlueprintStatics.h"
#include "PlayerHud.h"
#include "Kismet/GameplayStatics.h"

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
					chromaticAberrationIntensity = 0;
					vignetteIntensity = 0.4;
					
					ChangeCameraMaterial(0.0f);
					matIntensity = 0;
				}
			}

			// hide actor
			for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
			{
				AActor* Actor = *ActorItr;
		
				if (Actor->Tags.Contains("Sane"))
				{
					Actor->SetActorHiddenInGame(false);
				}
				if (Actor->Tags.Contains("Sweet"))
				{
					Actor->SetActorHiddenInGame(false);
				}
			}
			mvalue = "sane";

			//PlayerHud->Text = TEXT("");
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
						
						if (FullyMadSFX)
						{
							UFMODBlueprintStatics::PlayEventAtLocation(this, FullyMadSFX, Player->GetActorTransform(), true);	
						}
					}
				}
			}
			mmadnessBarValue = 0;
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

					ChangeCameraSettings(Settings, 10.0, 1.5);
					vignetteIntensity = 1.5;
					chromaticAberrationIntensity = 10;
					
					ChangeCameraMaterial(0.0f);
					matIntensity = 0;
				}

				APlayerHud* PlayerHud = Cast<APlayerHud>(PlayerController->GetHUD());
				if (PlayerHud)
				{
					PlayerHud->SetText("");  
				}
			}
			mvalue = "mad";
			

			// show actor
			for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
			{
				AActor* Actor = *ActorItr;
		
				if (Actor->Tags.Contains("Sane"))
				{
					Actor->SetActorHiddenInGame(true);
				}
				if (Actor->Tags.Contains("Sweet"))
				{
					Actor->SetActorHiddenInGame(false);
				}
			}
		}
	}
	else // sweat spot
	{
		if (mvalue != "sweat")
		{
			mvalue = "sweat";
			
			if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0))
			{
				APlayerHud* PlayerHud = Cast<APlayerHud>(PlayerController->GetHUD());
				if (PlayerHud)
				{
					PlayerHud->SetText("C to Focus");  
				}
			}

			
			// hide actor
			for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
			{
				AActor* Actor = *ActorItr;
		
				if (Actor->Tags.Contains("Sane"))
				{
					Actor->SetActorHiddenInGame(true);
				}
				if (Actor->Tags.Contains("Sweet"))
				{
					Actor->SetActorHiddenInGame(true);
				}
			}
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

void UMyUserWidget::Color(FPostProcessSettings& settings, float intensity)
{
	FPostProcessSettings& Settings = settings;

	Settings.bOverride_ColorSaturation = true;
	Settings.ColorSaturation = FVector4(intensity, intensity, intensity, 1.0f);
}

void UMyUserWidget::ChangeCameraMaterial(float intensity)
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

float UMyUserWidget::GetSweatSpotValue()
{
	return sweatSpot;
}

float UMyUserWidget::GetMadValue()
{
	return mad;
}

float UMyUserWidget::GetCurrentValue()
{
	return mmadnessBarValue;
}

void UMyUserWidget::SetIncreaseMadness(float value)
{
	increaseMadness = value;
}

void UMyUserWidget::IncreaseMadnessBar(float value)
{
	mmadnessBarValue += value;
}

TArray<float> UMyUserWidget::GetCameraSettings()
{
	return {chromaticAberrationIntensity, vignetteIntensity, matIntensity, colorIntensity};
}
