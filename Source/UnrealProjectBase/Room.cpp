// Fill out your copyright notice in the Description page of Project Settings.


#include "Room.h"
#include "Components/BoxComponent.h"
#include "Blueprint/UserWidget.h"
#include "MadnessMeter.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include <string>
#include  "GameFramework/Character.h"
#include "PlayerHud.h"
#include "Misc/OutputDeviceNull.h"

// Sets default values
ARoom::ARoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARoom::BeginPlay()
{
	Super::BeginPlay();

	for (UBoxComponent* Trigger : TriggerVolume)
	{
		if (Trigger)
		{
			Trigger->OnComponentBeginOverlap.AddDynamic(this, &ARoom::OnOverlapBegin);
		}
	}
}

// increment madness when enter the collision
void ARoom::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ACharacter* Character = Cast<ACharacter>(OtherActor))
	{
		if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
		{
			if (APlayerHud* MyHUD = Cast<APlayerHud>(PlayerController->GetHUD()))
			{
				UUserWidget* Widget = MyHUD->GetWidget();
				if (Widget)
				{
					UMadnessMeter* WidgetPtr = Cast<UMadnessMeter>(Widget);
					if (WidgetPtr)
					{
						WidgetPtr->isInRoom = true;
						WidgetPtr->SetIncreaseMadness(increment);

						if (UCameraComponent* Camera = Character->FindComponentByClass<UCameraComponent>())
						{
							FPostProcessSettings& Settings = Camera->PostProcessSettings;

							if (WidgetPtr->mvalue == "mad")
							{
								Color(Settings, 0.5, WidgetPtr->vignetteIntensity);
							}
							else
							{
								Color(Settings, 0.5, 1);	
							}
						}
					}
				}
			}
		}
	}
}

// madness stop rising when exit the collision
void ARoom::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	if (ACharacter* Character = Cast<ACharacter>(OtherActor))
	{
		if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
		{
			if (APlayerHud* MyHUD = Cast<APlayerHud>(PlayerController->GetHUD()))
			{
				UUserWidget* Widget = MyHUD->GetWidget();
				if (Widget)
				{
					UMadnessMeter* WidgetPtr = Cast<UMadnessMeter>(Widget);
			
					if (WidgetPtr)
					{
						WidgetPtr->isInRoom = false;
						WidgetPtr->SetIncreaseMadness(0.0);

						if (UCameraComponent* Camera = Character->FindComponentByClass<UCameraComponent>())
						{
							FPostProcessSettings& Settings = Camera->PostProcessSettings;
			
							Color(Settings, WidgetPtr->colorIntensity, WidgetPtr->vignetteIntensity);
						}
					}
				}
			}
		}
	}
}

void ARoom::Color(FPostProcessSettings& settings, float intensity, float Vignette)
{
	FPostProcessSettings& Settings = settings;
	
	Settings.bOverride_ColorSaturation = true;
	Settings.ColorSaturation = FVector4(intensity, intensity, intensity, 1.0f);

	Settings.bOverride_VignetteIntensity = true;
	Settings.VignetteIntensity = Vignette;
}

