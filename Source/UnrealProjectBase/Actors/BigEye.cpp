// All Rights Reserved by SweetSpot 2025-2026.


#include "BigEye.h"
#include "UnrealProjectBase/UI/PlayerHud.h"
#include "UnrealProjectBase/UI/MyUserWidget.h"

// Sets default values
ABigEye::ABigEye()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABigEye::BeginPlay()
{
	Super::BeginPlay();

	startTransform = GetTransform();
	Tags.Add("BigEye");

	GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
	{
		if (TObjectPtr<APlayerController> PlayerController = GetWorld()->GetFirstPlayerController())
		{
			TObjectPtr<APlayerHud> hud = Cast<APlayerHud>(PlayerController->GetHUD());

			MadnessWidget = Cast<UMyUserWidget>(hud->GetWidget());
		}
	});
}

void ABigEye::IncreaseMadness()
{
	if (count <= focusedLookTicks)
	{
		// increase madness when object is spotted
		MadnessWidget->IncreaseMadnessBar(increaseMadnessAmount);
	}
}

void ABigEye::FadeAway()
{
	if (count <= focusedLookTicks)
	{
		// make eye disappear 
		FVector Direction = -GetActorForwardVector();
		FVector CurrentLocation = GetActorLocation();
		FVector NewLocation = CurrentLocation + (Direction * 1);
		SetActorLocation(NewLocation);
		
		count++;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ABigEye::ResetPosition, 1.0f, false, 0.4f);
	}
	else
	{
		this->SetActorHiddenInGame(true);
		MadnessWidget->isImmune = true;
		GetWorldTimerManager().SetTimer(TimerHandleImmune, this, &ABigEye::RemoveImmunity, 1.0f, false, immunityTime);
	}
}

void ABigEye::ResetPosition()
{
	if (count <= focusedLookTicks)
	{
		SetActorTransform(startTransform);
		count = 0;
	}
}

void ABigEye::RemoveImmunity()
{
	MadnessWidget->isImmune = false;
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Removing Immunity");
	this->Destroy();
}
