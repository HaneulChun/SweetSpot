// Fill out your copyright notice in the Description page of Project Settings.


#include "Room.h"
#include "Components/BoxComponent.h"
#include "Blueprint/UserWidget.h"
#include "UnrealProjectBase/UI/PlayerHud.h"
#include "UnrealProjectBase/UI/MyUserWidget.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"

// Sets default values
ARoom::ARoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UBoxComponent* triggerBox;
	
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
				if (UUserWidget* Widget = MyHUD->GetWidget())
				{
					UMyUserWidget* WidgetPtr = Cast<UMyUserWidget>(Widget);
					if (WidgetPtr)
					{
						// increase Madness if player is in room
						WidgetPtr->isInRoom = true;
						WidgetPtr->SetIncreaseMadness(increment);

						// give the player vignette
						if (WidgetPtr->mvalue == "mad")
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
					UMyUserWidget* WidgetPtr = Cast<UMyUserWidget>(Widget);
			
					if (WidgetPtr)
					{
						// increase Madness if player is in room
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

