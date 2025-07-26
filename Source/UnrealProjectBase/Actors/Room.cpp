// Fill out your copyright notice in the Description page of Project Settings.


#include "Room.h"
#include "Components/BoxComponent.h"
#include "UnrealProjectBase/UI/PlayerHud.h"
#include "UnrealProjectBase/UI/MyUserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "UnrealProjectBase/Component/CameraSettingsComponent.h"

// Sets default values
ARoom::ARoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
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

	GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		APlayerHud* hud = Cast<APlayerHud>(PlayerController->GetHUD());

		widget = Cast<UMyUserWidget>(hud->GetMadnessMeterWidget());

		// point at the player's camera and add material
		Camera = PlayerController->PlayerCameraManager->GetOwningPlayerController()->PlayerCameraManager->ViewTarget.Target->FindComponentByClass<UCameraComponent>();

		CameraSettings = PlayerController->GetPawn()->FindComponentByClass<UCameraSettingsComponent>();
	});

	if (increment <=0)
	{
		fieldOfView = 90;
	}
}

// increment madness when enter the collision
void ARoom::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!Cast<ACharacter>(OtherActor)) return;
	if (!Cast<UCapsuleComponent>(OtherComp)) return;

	if (!widget) return;
	
	if (increment < 0)
	{
		widget->isInLight = true;
	}
	else
	{
		widget->isInRoom = true;
	}
	// increase Madness if player is in room
	widget->SetIncreaseMadness(increment);
						
	// give the player vignette
	if (widget->CurrentState == ECurrentState::Mad)
	{
		CameraSettings->SetCameraSettings(colorIntensity, widget->vignetteIntensity, fieldOfView);
	}
	else
	{
		if (increment < 0)
		{
			CameraSettings->SetCameraSettings(colorIntensity, 0.4, fieldOfView);
		}
		else
		{
			CameraSettings->SetCameraSettings(colorIntensity, 1, fieldOfView);
		}
	}
}

// madness stop rising when exit the collision
void ARoom::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (!Cast<ACharacter>(OtherActor)) return;
	if (!Cast<UCapsuleComponent>(OtherComp)) return;

	if (!widget) return;
	
	// increase Madness if player is in room
	if (increment < 0)
	{
		widget->isInLight = false;
		if (widget->isInRoom == true)
		{
			widget->SetIncreaseMadness(widget->roomMadnessDamage);
			CameraSettings->SetCameraSettings(0.5, 1, 110);
		}
		else
		{
			widget->SetIncreaseMadness(0.0);

			// remove the player vignette when exiting room
			CameraSettings->SetCameraSettings(widget->colorIntensity, widget->vignetteIntensity, 90);
		}
	}
	else
	{
		widget->isInRoom = false;
		widget->SetIncreaseMadness(0.0);

		// remove the player vignette when exiting room
		CameraSettings->SetCameraSettings(widget->colorIntensity, widget->vignetteIntensity, 90);
	}
}