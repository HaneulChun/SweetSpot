// All Rights Reserved by Jason 2025-2026.


#include "SpottedObject.h"

#include "UnrealProjectBase/UI/PlayerHud.h"
#include "UnrealProjectBase/UI/MyUserWidget.h"

// Sets default values for this component's properties
USpottedObject::USpottedObject()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}


// Called when the game starts
void USpottedObject::BeginPlay()
{
	Super::BeginPlay();

	startTransform = GetOwner()->GetTransform();
	GetOwner()->Tags.Add("SeeMe");
	
	GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		APlayerHud* hud = Cast<APlayerHud>(PlayerController->GetHUD());

		widget = Cast<UMyUserWidget>(hud->GetMadnessMeterWidget());
	});
}

// make object fade into wall/floor
void USpottedObject::FadeAway_Implementation()
{
	FadeAway();
	if (count <= focusedLookTicks)
	{
		isClosingAnim = true;
		
		// make eye disappear 
		FVector Direction = -GetOwner()->GetActorForwardVector();
		FVector CurrentLocation = GetOwner()->GetActorLocation();
		FVector NewLocation = CurrentLocation + (Direction * speed);
		GetOwner()->SetActorLocation(NewLocation);
		
		count++;
		GetOwner()->GetWorldTimerManager().SetTimer(TimerHandle, this, &USpottedObject::ResetPosition_Implementation, 1.0f, false, 0.4f);
	}
	else
	{
		widget->DecreaseMadness(restoreMadnessValue);
		GetOwner()->Destroy();
	}
}

void USpottedObject::ResetPosition_Implementation()
{
	GetOwner()->SetActorTransform(startTransform);
	count = 0;
	
	ResetPosition();
	isClosingAnim = false;
}

void USpottedObject::LookAtPlayer_Implementation()
{
}

void USpottedObject::IncreaseMadness()
{
	if (widget)
	{
		widget->IncreaseMadnessBar(increaseMadnessAmount);
	}
}
