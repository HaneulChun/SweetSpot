// All Rights Reserved by SweetSpot 2025-2026.

#include "UnrealProjectBase/Wristwatch/Public/Random_BPM_Numbers.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "UObject/UObjectIterator.h"

// Sets default values
ARandom_BPM_Numbers::ARandom_BPM_Numbers()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARandom_BPM_Numbers::BeginPlay()
{
	Super::BeginPlay();

	// Find any instance of UMyUserWidget that is in the viewport
	for (TObjectIterator<UMyUserWidget> WidgetItr; WidgetItr; ++WidgetItr)
	{
		if (WidgetItr->IsValidLowLevel() && WidgetItr->IsInViewport())
		{
			UserWidgetRef = *WidgetItr;
			break;
		}
	}

	if (UserWidgetRef && UserWidgetRef->CurrentWidget)
	{
		// Attempt to get the BPM text block from the widget
		BPMText = Cast<UTextBlock>(
			UserWidgetRef->CurrentWidget->GetWidgetFromName(TEXT("Text_BPM_Numbers")));

		if (!BPMText)
		{
			UE_LOG(LogTemp, Warning, TEXT("Text_BPM_Numbers not found in widget."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UMyUserWidget or CurrentWidget not found."));
	}
}

// Called every frame
void ARandom_BPM_Numbers::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateBPMDisplay();
}

void ARandom_BPM_Numbers::UpdateBPMDisplay()
{
	if (!UserWidgetRef || !BPMText) return;

	// Get madness state values
	const float Madness = UserWidgetRef->GetCurrentValue();
	const float Sweat = UserWidgetRef->GetSweatSpotValue();
	const float Mad = UserWidgetRef->GetMadValue();

	int32 BPM = 0;

	// Determine BPM range by madness level
	if (Madness <= Sweat)
	{
		BPM = FMath::RandRange(60, 100); // Resting
	}
	else if (Madness >= Mad)
	{
		BPM = FMath::RandRange(170, 220); // Insane
	}
	else
	{
		BPM = FMath::RandRange(101, 169); // Sweet Spot
	}

	// Update the text block
	const FString BPMString = FString::Printf(TEXT("%d BPM"), BPM);
	BPMText->SetText(FText::FromString(BPMString));
}
