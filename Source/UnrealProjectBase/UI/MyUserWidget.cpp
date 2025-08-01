// All Rights Reserved by Sweet Spot 2025-2026.

#include "MyUserWidget.h"

#include "Engine/Scene.h"
#include "FMODBlueprintStatics.h"
#include "PlayerHud.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UnrealProjectBase/Actors/SweetSpotCharacter.h"
#include "UnrealProjectBase/Component/CameraSettingsComponent.h"
#include "UnrealProjectBase/PlayerComponent/FadeObjectComponent.h"
#include "Engine/LevelStreaming.h"

void UMyUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	bIsFocusable = true;

	if (TObjectPtr<APlayerController> PlayerController = GetWorld()->GetFirstPlayerController())
	{
		CameraSettings = PlayerController->GetPawn()->FindComponentByClass<UCameraSettingsComponent>();

		if (TObjectPtr<APawn> t = PlayerController->GetPawn())
		{
			Player = t;
		}

		FadeObject = PlayerController->GetPawn()->FindComponentByClass<UFadeObjectComponent>();
	}
	
	GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
	{
		if (TObjectPtr<APlayerController> PlayerController = GetWorld()->GetFirstPlayerController())
		{
			if (TObjectPtr<APlayerHud> PlayerHud = Cast<APlayerHud>(PlayerController->GetHUD()))
			{
				playerHud = PlayerHud;  
			}
		}
	});
}

void UMyUserWidget::CheckPlayerState()
{
	if(currentMadnessBarValue <= sweetSpot) // sane 
	{
		if (CurrentState != ECurrentState::Sane)
		{
			// change camera settings and material
			CameraSettings->ChangeCameraSettings(0.0, 0.4);
			chromaticAberrationIntensity = 0;
			vignetteIntensity = 0.4;
			
			CameraSettings->ChangeCameraMaterial(0.0f);
			matIntensity = 0;

			// hide actor
			FadeObject->Fade(-0.1, 1, -0.1, 1);
			
			CurrentState = ECurrentState::Sane;
			ChangedPlayerState();
		}
	}
	else if(currentMadnessBarValue >= 1) // dead 
	{
		if (CurrentState != ECurrentState::Dead)
		{
			// reset the player
			//GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UMyUserWidget::Dying, 0.1, true);
			ASweetSpotCharacter* MyCharacter = Cast<ASweetSpotCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			MyCharacter->DeathCameraMovement();
			
			UnFocus();

			
			CurrentState = ECurrentState::Dead;
			ChangedPlayerState();
		}
	}
	else if(currentMadnessBarValue >= mad) // mad
	{
		if (CurrentState != ECurrentState::Mad)
		{
			// change camera settings and material
			CameraSettings->ChangeCameraSettings(10.0, 1.5);
			chromaticAberrationIntensity = 10;
			vignetteIntensity = 1.5;
			
			// show actor
			FadeObject->Fade(0, 1, 0, 1);
			
			CurrentState = ECurrentState::Mad;
			ChangedPlayerState();
		}
	}
	else // sweet spot
	{
		if (CurrentState != ECurrentState::SweetSpot)
		{
			if (isInRoom)
			{
				CameraSettings->ChangeCameraSettings(0.0, 1);
				chromaticAberrationIntensity = 0;
				vignetteIntensity = 0.4;
			}
			else
			{
				CameraSettings->ChangeCameraSettings(0.0, .4);
				chromaticAberrationIntensity = 0;
				vignetteIntensity = 0.4;
			}
			
			// hide actor
			if (CurrentState == ECurrentState::Mad)
			{
				FadeObject->Fade(0, 1, 0, 1);
			}
			else
			{
				FadeObject->Fade(0.1, 0, 0.1, 0);
			}

			CurrentState = ECurrentState::SweetSpot;
			ChangedPlayerState();
		}
	}
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
	
	if (currentMadnessBarValue <= 0.2f)
	{
		currentMadnessBarValue = 0.2f;
	}
}

void UMyUserWidget::IncreaseMadnessBar(float value)
{
	if (hasKey == true)
	{
		currentMadnessBarValue += value;
	}
}

void UMyUserWidget::Dead()
{
	SpawnPlayer();
						
	if (FullyMadSFX)
	{
		UFMODBlueprintStatics::PlayEventAtLocation(this, FullyMadSFX, Player->GetActorTransform(), true);	
	}
	
	ASweetSpotCharacter* MyCharacter = Cast<ASweetSpotCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	MyCharacter->Dead();
	
	currentMadnessBarValue = 0;
}

void UMyUserWidget::SpawnPlayer()
{
	// find object with spawn tag and teleport to spawn
	if (FadeObject->spawnPoint)
	{
		Player->Controller->SetControlRotation(FadeObject->spawnPoint->FindComponentByClass<UArrowComponent>()->GetComponentRotation());
		Player->SetActorLocation(FadeObject->spawnPoint->FindComponentByClass<UArrowComponent>()->GetComponentLocation());
	}
}
