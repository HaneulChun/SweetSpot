// All Rights Reserved by Sweet Spot 2025-2026.

#include "MyUserWidget.h"

#include "EngineUtils.h"
#include "Camera/CameraComponent.h"
#include "Engine/Scene.h"
#include "FMODBlueprintStatics.h"
#include "PlayerHud.h"

void UMyUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	bIsFocusable = true;

	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		AActor* Actor = *ActorItr;
		
		if (Actor->Tags.Contains("Sane"))
		{
			SaneActors.Add(Actor);
		}
		if (Actor->Tags.Contains("Sweet"))
		{
			SweetActors.Add(Actor);
		}
	}

	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		AActor* Actor = *ActorItr;
		
		if (Actor->Tags.Contains("Spawn"))
		{
			spawnPoint = Actor;
		}
	}
}

void UMyUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if(currentMadnessBarValue <= sweatSpot) // sane 
	{
		if (mvalue != "sane")
		{
			ChangeCameraSettings(0.0, 0.4);
			chromaticAberrationIntensity = 0;
			vignetteIntensity = 0.4;
					
			ChangeCameraMaterial(0.0f);
			matIntensity = 0;

			// hide actor
			Fade(-0.1, 1, -0.1, 1);
			for (AActor* Actor : SaneActors)
			{
				Actor->SetActorEnableCollision(false);
			}
			for (AActor* Actor : SweetActors)
			{
				Actor->SetActorEnableCollision(false);
			}
			mvalue = "sane";
			
			// set text 
			if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
			{
				APlayerHud* PlayerHud = Cast<APlayerHud>(PlayerController->GetHUD());
				if (PlayerHud)
				{
					PlayerHud->SetText("");  
				}
			}
		}
	}
	else if(currentMadnessBarValue >= 1) // dead 
	{
		if (mvalue != "dead")
		{
			isDying = true;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UMyUserWidget::Dying, 0.1, isDying);
			mvalue = "dead";
		}
	}
	else if(currentMadnessBarValue >= mad) // mad
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
			Fade(0, 1, -0.1, 1);
			for (AActor* Actor : SaneActors)
			{
				Actor->SetActorEnableCollision(true);
			}
			for (AActor* Actor : SweetActors)
			{
				Actor->SetActorEnableCollision(false);
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
			Fade(0.1, 0, 0.1, 0);
			for (AActor* Actor : SaneActors)
			{
				Actor->SetActorEnableCollision(true);
			}
			for (AActor* Actor : SweetActors)
			{
				Actor->SetActorEnableCollision(true);
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
	return currentMadnessBarValue;
}

void UMyUserWidget::SetIncreaseMadness(float value)
{
	increaseMadness = value;
}

void UMyUserWidget::DecreaseMadness(float value)
{
	currentMadnessBarValue -= value;
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
	currentMadnessBarValue += value;
}



void UMyUserWidget::Fade_Implementation(float saneTime, float saneStartValue, float sweetTime, float sweetStartValue)
{
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
			Player->SetActorLocation(spawnPoint->GetActorLocation());
						
			if (FullyMadSFX)
			{
				UFMODBlueprintStatics::PlayEventAtLocation(this, FullyMadSFX, Player->GetActorTransform(), true);	
			}
		}
		currentMadnessBarValue = 0;
	}
}