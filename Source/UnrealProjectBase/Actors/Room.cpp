// Fill out your copyright notice in the Description page of Project Settings.


#include "Room.h"
#include "Components/BoxComponent.h"
#include "Blueprint/UserWidget.h"
#include "UnrealProjectBase/UI/PlayerHud.h"
#include "UnrealProjectBase/UI/MyUserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ARoom::ARoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// set trigger-box for default
	triggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	triggerBox->SetupAttachment(RootComponent);
	triggerBox->SetCollisionProfileName(TEXT("Trigger"));
	triggerBox->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void ARoom::BeginPlay()
{
	Super::BeginPlay();

	triggerBox->OnComponentBeginOverlap.AddDynamic(this, &ARoom::OnOverlapBegin);
	triggerBox->OnComponentEndOverlap.AddDynamic(this, &ARoom::OnOverlapEnd);
	
	for (UBoxComponent* Trigger : TriggerVolume)
	{
		if (Trigger)
		{
			Trigger->OnComponentBeginOverlap.AddDynamic(this, &ARoom::OnOverlapBegin);
			Trigger->OnComponentEndOverlap.AddDynamic(this, &ARoom::OnOverlapEnd);
		}
	}
}

// increment madness when enter the collision
void ARoom::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APawn* OverlappingPawn = Cast<APawn>(OtherActor))
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(OverlappingPawn->GetController()))
		{
			if (Cast<UCapsuleComponent>(OtherComp))
			{
				if (APlayerHud* MyHUD = Cast<APlayerHud>(PlayerController->GetHUD()))
				{
					if (UUserWidget* Widget = MyHUD->GetWidget())
					{
						if (UMyUserWidget* WidgetPtr = Cast<UMyUserWidget>(Widget))
						{
							if (increment < 0)
							{
								WidgetPtr->isInLight = true;
							}
							else
							{
								WidgetPtr->isInRoom = true;
							}
							// increase Madness if player is in room
							WidgetPtr->SetIncreaseMadness(increment);
						
							// give the player vignette
							if (WidgetPtr->CurrentState == ECurrentState::Mad)
							{
								Color(colorIntensity, WidgetPtr->vignetteIntensity);
							}
							else
							{
								Color(colorIntensity, 1);	
							}
						}
					}
				}
			}
		}
	}
}

// madness stop rising when exit the collision
void ARoom::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (APawn* OverlappingPawn = Cast<APawn>(OtherActor))
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(OverlappingPawn->GetController()))
		{
			if (Cast<UCapsuleComponent>(OtherComp))
			{
				if (APlayerHud* MyHUD = Cast<APlayerHud>(PlayerController->GetHUD()))
				{
					if (UUserWidget* Widget = MyHUD->GetWidget())
					{
						if (UMyUserWidget* WidgetPtr = Cast<UMyUserWidget>(Widget))
						{
							// increase Madness if player is in room
							if (increment < 0)
							{
								WidgetPtr->isInLight = false;
								if (WidgetPtr->isInRoom == true)
								{
									WidgetPtr->SetIncreaseMadness(0.05);
									Color(.5, 1);
								}
								else
								{
									WidgetPtr->SetIncreaseMadness(0.0);

									// remove the player vignette when exiting room
									Color(WidgetPtr->colorIntensity, WidgetPtr->vignetteIntensity);
								}
							}
							else
							{
								WidgetPtr->isInRoom = false;
								WidgetPtr->SetIncreaseMadness(0.0);

								// remove the player vignette when exiting room
								Color(WidgetPtr->colorIntensity, WidgetPtr->vignetteIntensity);
							}
						}
					}
				}
			}
		}
	}
}

void ARoom::Color(float intensity, float Vignette)
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		// point at the player's camera and add material
		if (UCameraComponent* Camera = PlayerController->PlayerCameraManager->GetOwningPlayerController()->PlayerCameraManager->ViewTarget.Target->FindComponentByClass<UCameraComponent>())
		{
			FPostProcessSettings& Settings = Camera->PostProcessSettings;

			Settings.bOverride_ColorSaturation = true;
			Settings.ColorSaturation = FVector4(intensity, intensity, intensity, 1.0f);

			Settings.bOverride_VignetteIntensity = true;
			Settings.VignetteIntensity = Vignette;
		}
	}
}

