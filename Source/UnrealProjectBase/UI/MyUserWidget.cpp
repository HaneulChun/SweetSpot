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
}

void UMyUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if(mmadnessBarValue <= sweatSpot) // sane 
	{
		if (mvalue != "sane")
		{
			ChangeCameraSettings(0.0, 0.4);
			chromaticAberrationIntensity = 0;
			vignetteIntensity = 0.4;
					
			ChangeCameraMaterial(0.0f);
			matIntensity = 0;

			// hide actor
			for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
			{
				AActor* Actor = *ActorItr;
		
				if (Actor->Tags.Contains("Sane"))
				{
					Actor->SetActorHiddenInGame(true);
					Actor->SetActorEnableCollision(false);
				}
				if (Actor->Tags.Contains("Sweet"))
				{
					Actor->SetActorHiddenInGame(false);
					Actor->SetActorEnableCollision(true);
				}
			}
			mvalue = "sane";

			//PlayerHud->Text = TEXT("");
		}
	}
	else if(mmadnessBarValue >= 1) // dead 
	{
		if (mvalue != "dead")
		{
			isDying = true;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UMyUserWidget::Dying, 0.1, isDying);
			mvalue = "dead";
		}
	}
	else if(mmadnessBarValue >= mad) // mad
	{
		if (mvalue != "mad")
		{
			ChangeCameraSettings(10.0, 1.5);
			vignetteIntensity = 1.5;
			chromaticAberrationIntensity = 10;
					
			ChangeCameraMaterial(0.0f);
			matIntensity = 0;

			// set text 
			if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
			{
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
					Actor->SetActorHiddenInGame(false);
					Actor->SetActorEnableCollision(true);
				}
				if (Actor->Tags.Contains("Sweet"))
				{
					Actor->SetActorHiddenInGame(false);
					Actor->SetActorEnableCollision(true);
				}
			}
		}
	}
	else // sweat spot
	{//colorIntensity
		if (mvalue != "sweat")
		{
			mvalue = "sweat";

			ChangeCameraSettings(0.0, .4);
			chromaticAberrationIntensity = 0;
			vignetteIntensity = 0.4;
			
			// check if player can focus in an object
			// if there is no object to focus dont show text
			for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
			{
				AActor* Actor = *ActorItr;
				if (Actor)
				{
					if (UMeshComponent* MeshComp = Actor->FindComponentByClass<UMeshComponent>())
					{
						if (MeshComp->CustomDepthStencilValue == 1)
						{
							if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
							{
								APlayerHud* PlayerHud = Cast<APlayerHud>(PlayerController->GetHUD());
								if (PlayerHud)
								{
									PlayerHud->SetText("C to Focus");  
								}
							}
							break;
						}
					}
				}
			}
			
			// hide actor
			for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
			{
				AActor* Actor = *ActorItr;
		
				if (Actor->Tags.Contains("Sane"))
				{
					Actor->SetActorHiddenInGame(false);
					Actor->SetActorEnableCollision(true);
				}
				if (Actor->Tags.Contains("Sweet"))
				{
					Actor->SetActorHiddenInGame(true);
					Actor->SetActorEnableCollision(false);
				}
			}
		}
	}
}


void UMyUserWidget::SetMaterial(TArray<UMaterialInterface*> Mat)
{
	Material = Mat;
}

void UMyUserWidget::ChangeCameraSettings(float chromaticAberration, float Vignette)
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

void UMyUserWidget::Color(float intensity)
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		// point at the player's camera
		if (UCameraComponent* Camera = PlayerController->PlayerCameraManager->GetOwningPlayerController()->PlayerCameraManager->ViewTarget.Target->FindComponentByClass<UCameraComponent>())
		{
			FPostProcessSettings& Settings = Camera->PostProcessSettings;
			
			Settings.bOverride_ColorSaturation = true;
			Settings.ColorSaturation = FVector4(intensity, intensity, intensity, 1.0f);
		}
	}
}

void UMyUserWidget::ChangeCameraMaterial(float intensity)
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		// point at the player's camera and add material
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

void UMyUserWidget::DecreaseMadness(float value)
{
	mmadnessBarValue -= value;
	if (isInRoom)
	{
		ChangeCameraSettings(0.0, 1);
		Color(0.5);
	}
	else
	{
		ChangeCameraSettings(0.0, .4);
	}
}

void UMyUserWidget::IncreaseMadnessBar(float value)
{
	mmadnessBarValue += value;
}

void UMyUserWidget::Dying()
{
	dyingCount++;
	ChangeCameraSettings(10.0, (dyingCount * 0.5) + 1.5);
	if (dyingCount >= 10)
	{
		isDying = false;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UMyUserWidget::Dead, 0.1, isDying);
		dyingCount = 0;
	}
}

void UMyUserWidget::Dead()
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

TArray<float> UMyUserWidget::GetCameraSettings()
{
	return {chromaticAberrationIntensity, vignetteIntensity, matIntensity, colorIntensity};
}
