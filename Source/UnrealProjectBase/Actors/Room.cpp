// Fill out your copyright notice in the Description page of Project Settings.


#include "Room.h"
#include "Components/BoxComponent.h"
#include "Blueprint/UserWidget.h"
#include "UnrealProjectBase/UI/PlayerHud.h"
#include "UnrealProjectBase/UI/MyUserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"

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
	});
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
		Color(colorIntensity, widget->vignetteIntensity);
	}
	else
	{
		if (increment < 0)
		{
			Color(colorIntensity, 0.4);	
		}
		else
		{
			Color(colorIntensity, 1);	
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
			Color(.5, 1);
		}
		else
		{
			widget->SetIncreaseMadness(0.0);

			// remove the player vignette when exiting room
			Color(widget->colorIntensity, widget->vignetteIntensity);
		}
	}
	else
	{
		widget->isInRoom = false;
		widget->SetIncreaseMadness(0.0);

		// remove the player vignette when exiting room
		Color(widget->colorIntensity, widget->vignetteIntensity);
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