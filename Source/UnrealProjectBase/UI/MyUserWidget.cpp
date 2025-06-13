// All Rights Reserved by Sweet Spot 2025-2026.

#include "MyUserWidget.h"

#include "EngineUtils.h"
#include "Camera/CameraComponent.h"
#include "Engine/Scene.h"
#include "FMODBlueprintStatics.h"
#include "PlayerHud.h"
#include "UnrealProjectBase/PlayerComponent/PlayerVision.h"

void UMyUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	bIsFocusable = true;

	StartLoop();
	
	
	GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
	{
		if (TObjectPtr<APlayerController> PlayerController = GetWorld()->GetFirstPlayerController())
		{
			if (TObjectPtr<APlayerHud> PlayerHud = Cast<APlayerHud>(PlayerController->GetHUD()))
			{
				playerHud = PlayerHud;  
			}

			// point at the player's camera
			if (TObjectPtr<UCameraComponent> Camera = PlayerController->PlayerCameraManager->GetOwningPlayerController()->PlayerCameraManager->ViewTarget.Target->FindComponentByClass<UCameraComponent>())
			{
				playerCamera = Camera;
			}

			if (TObjectPtr<APawn> t = PlayerController->GetPawn())
			{
				Player = t;
			}
		}
	});
}

void UMyUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if(currentMadnessBarValue <= sweetSpot) // sane 
	{
		if (CurrentState != ECurrentState::Sane)
		{
			// change camera settings and matreial
			ChangeCameraSettings(0.0, 0.4);
			chromaticAberrationIntensity = 0;
			vignetteIntensity = 0.4;
			
			ChangeCameraMaterial(0.0f);
			matIntensity = 0;

			// hide actor
			Fade(-0.1, 1, -0.1, 1);
			for (AActor* Actor : SaneActors)
			{
				if (IsValid(Actor))
				{
					Actor->SetActorEnableCollision(false);
				}
			}
			for (AActor* Actor : SweetActors)
			{
				if (IsValid(Actor))
				{
					Actor->SetActorEnableCollision(false);
				}
			}
			CurrentState = ECurrentState::Sane;
			
			// set text 
			playerHud->SetText("");  
		}
	}
	else if(currentMadnessBarValue >= 1) // dead 
	{
		if (CurrentState != ECurrentState::Dead)
		{
			// reset the player
			isDying = true;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UMyUserWidget::Dying, 0.1, isDying);
			CurrentState = ECurrentState::Dead;
		}
	}
	else if(currentMadnessBarValue >= mad) // mad
	{
		if (CurrentState != ECurrentState::Mad)
		{
			// change camera settings and material
			ChangeCameraSettings(10.0, 1.5);
			chromaticAberrationIntensity = 10;
			vignetteIntensity = 1.5;
			
			ChangeCameraMaterial(0.0f);
			matIntensity = 0;

			// set text
			playerHud->SetText("");  

			CurrentState = ECurrentState::Mad;
			
			// show actor
			Fade(0, 1, 0, 1);
			for (AActor* Actor : SaneActors)
			{
				if (IsValid(Actor))
				{
					Actor->SetActorEnableCollision(true);
				}
			}
			for (AActor* Actor : SweetActors)
			{
				if (IsValid(Actor))
				{
					Actor->SetActorEnableCollision(true);
				}
			}
		}
	}
	else // sweat spot
	{
		if (CurrentState != ECurrentState::SweetSpot)
		{
			if (isInRoom)
			{
				ChangeCameraSettings(0.0, 1);
				chromaticAberrationIntensity = 0;
				vignetteIntensity = 0.4;
			}
			else
			{
				ChangeCameraSettings(0.0, .4);
				chromaticAberrationIntensity = 0;
				vignetteIntensity = 0.4;
			}
			
			// check if player can focus in an object
			// if there is no object to focus don't show text
			for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
			{
				if (AActor* Actor = *ActorItr)
				{
					if (UMeshComponent* MeshComp = Actor->FindComponentByClass<UMeshComponent>())
					{
						if (MeshComp->CustomDepthStencilValue == 1)
						{
							playerHud->SetText("C to Focus");
							
							break;
						}
					}
				}
			}
			
			// hide actor
			if (CurrentState == ECurrentState::Mad)
			{
				Fade(0, 1, 0.1, 0);
			}
			else
			{
				Fade(0.1, 0, 0.1, 0);
			}
			for (AActor* Actor : SaneActors)
			{
				if (IsValid(Actor))
				{
					Actor->SetActorEnableCollision(true);
				}
			}
			for (AActor* Actor : SweetActors)
			{
				if (IsValid(Actor))
				{
					Actor->SetActorEnableCollision(true);
				}
			}
			
			CurrentState = ECurrentState::SweetSpot;
		}
	}
}


void UMyUserWidget::SetMaterial(TArray<UMaterialInterface*> Mat)
{
	Material = Mat;
}

void UMyUserWidget::ChangeCameraSettings(float chromaticAberration, float Vignette)
{
	FPostProcessSettings& Settings = playerCamera->PostProcessSettings;

	Settings.bOverride_SceneFringeIntensity = true;
	Settings.SceneFringeIntensity = chromaticAberration;

	Settings.bOverride_VignetteIntensity = true;
	Settings.VignetteIntensity = Vignette;
}

void UMyUserWidget::Color(float intensity)
{
	FPostProcessSettings& Settings = playerCamera->PostProcessSettings;
			
	Settings.bOverride_ColorSaturation = true;
	Settings.ColorSaturation = FVector4(intensity, intensity, intensity, 1.0f);
}

void UMyUserWidget::ChangeCameraMaterial(float intensity)
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

void UMyUserWidget::CheckForSubLevel(TSoftObjectPtr<UWorld> unloadedSubLevel)
{
	// loop until the level is unloaded to set the SweetSpotActors
	GetWorld()->GetTimerManager().SetTimer(TimerHandleLevel, [this, unloadedSubLevel]()
	{
		if (!unloadedSubLevel.IsValid())
		{
			StartLoop();

			// set the array for tentacle and eyes
			if (TObjectPtr<APlayerController> PlayerController = GetWorld()->GetFirstPlayerController())
			{
				if (TObjectPtr<UPlayerVision> playerVision = PlayerController->GetPawn()->FindComponentByClass<UPlayerVision>())
				{
					playerVision->SetActorArray();	
				}
			}
			
			GetWorld()->GetTimerManager().ClearTimer(TimerHandleLevel);
		}
	}, 0.2f, true);
}

float UMyUserWidget::GetSweetSpotValue()
{
	return sweetSpot;
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
	if (value > 0)
	{
		roomMadnessDamage = value;
	}
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
	if (isImmune == false)
	{
		currentMadnessBarValue += value;
	}
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
	if (spawnPoint)
	{
		Player->SetActorLocation(spawnPoint->GetActorLocation());
	}
						
	if (FullyMadSFX)
	{
		UFMODBlueprintStatics::PlayEventAtLocation(this, FullyMadSFX, Player->GetActorTransform(), true);	
	}
	currentMadnessBarValue = 0;
}

void UMyUserWidget::StartLoop()
{
	CurrentState = ECurrentState::Dead;
	SaneActors.Empty();
	SweetActors.Empty();
	spawnPoint = nullptr;
	
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		TObjectPtr<AActor> Actor = *ActorItr;

		
		if (Actor->Tags.Contains("Sane"))
		{
			SaneActors.Add(Actor);
		}
		else if (Actor->Tags.Contains("Sweet"))
		{
			SweetActors.Add(Actor);
		}
		else if (Actor->Tags.Contains("Spawn"))
		{
			spawnPoint = Actor;
		}
	}
}
