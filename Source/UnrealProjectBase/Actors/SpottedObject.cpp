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
	
	GetOwner()->Tags.Add("SeeMe");
}


// Called every frame
void USpottedObject::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (isFading == true)
	{
		if (spotted == false)
		{
			// increase madness when object is sopoted
			if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
			{
				APlayerHud* hud = Cast<APlayerHud>(PlayerController->GetHUD());

				UMyUserWidget* widget = Cast<UMyUserWidget>(hud->GetWidget());
				if (widget)
				{
					widget->IncreaseMadnessBar(increaseMadness);
				}	
			}
			spotted = true;
		}

		// move the object
		FVector Direction = -GetOwner()->GetActorForwardVector();
		FVector CurrentLocation = GetOwner()->GetActorLocation();
		FVector NewLocation = CurrentLocation + (Direction * speed);

		GetOwner()->SetActorLocation(NewLocation);
		if (CurrentLocation.Z <= -200)
		{
			isFading = false;
		}
	}
}

void USpottedObject::FadeAway()
{
	isFading = true;
}

