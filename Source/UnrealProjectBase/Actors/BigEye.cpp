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

	GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
	{
		if (TObjectPtr<APlayerController> PlayerController = GetWorld()->GetFirstPlayerController())
		{
			TObjectPtr<APlayerHud> hud = Cast<APlayerHud>(PlayerController->GetHUD());

			MadnessWidget = Cast<UMyUserWidget>(hud->GetMadnessMeterWidget());
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

void ABigEye::FadeAway_Implementation()
{
	if (count <= focusedLookTicks)
	{
		// make eye disappear 
		FVector Direction = -GetActorForwardVector();
		FVector CurrentLocation = GetActorLocation();
		FVector NewLocation = CurrentLocation + (Direction * 1);
		SetActorLocation(NewLocation);
		
		count++;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ABigEye::ResetPosition_Implementation, 1.0f, false, 0.4f);
		
		FadeAway();
	}
	else
	{
		this->SetActorHiddenInGame(true);
		MadnessWidget->DecreaseMadness(restoreMadnessValue);
		
		// give immune to player madness meter 
		//MadnessWidget->isImmune = true;
		//GetWorldTimerManager().SetTimer(TimerHandleImmune, this, &ABigEye::RemoveImmunity, 1.0f, false, immunityTime);

		// only if no immunity
		this->Destroy();
	}
}


void ABigEye::ResetPosition_Implementation()
{
	if (count <= focusedLookTicks)
	{
		SetActorTransform(startTransform);
		count = 0;
		ResetPosition();
	}
}

void ABigEye::RemoveImmunity()
{
	MadnessWidget->hasKey = false;
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Removing Immunity");
	this->Destroy();
}
