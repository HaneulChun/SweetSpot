// All Rights Reserved by SweetSpot 2025-2026.


#include "SweetSpotGameMode.h"

#include "UnrealProjectBase/PlayerComponent/FadeObjectComponent.h"
#include "UnrealProjectBase/PlayerComponent/PlayerVision.h"

void ASweetSpotGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (TObjectPtr<APlayerController> PlayerController = GetWorld()->GetFirstPlayerController())
	{
		FadeObject = PlayerController->GetPawn()->FindComponentByClass<UFadeObjectComponent>();
	}
}

void ASweetSpotGameMode::SetLevel()
{
	// Call helper when level is unloaded
	FadeObject->StartLoop();

	// set the array for tentacle and eyes
	if (TObjectPtr<APlayerController> PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (TObjectPtr<UPlayerVision> playerVision = PlayerController->GetPawn()->FindComponentByClass<UPlayerVision>())
		{
			playerVision->SetActorArray();
		}
	}
}
