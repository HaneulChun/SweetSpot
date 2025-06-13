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

	// if (UserWidgetRef)
	// {
	// 	// Attempt to get the BPM text block from the widget
	// 	Text_BPM_Numbers = Cast<UTextBlock>(
	// 		UserWidgetRef->GetWidgetFromName(TEXT("Text_BPM_Numbers")));
	//
	// 	if (!Text_BPM_Numbers)
	// 	{
	// 		UE_LOG(LogTemp, Warning, TEXT("Text_BPM_Numbers not found in widget."));
	// 	}
	// }
	// else
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("UMyUserWidget or CurrentWidget not found."));
	// }
}

// Called every frame
void ARandom_BPM_Numbers::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARandom_BPM_Numbers::FreezeLook()
{
	UpdateBPMDisplay();
}

void ARandom_BPM_Numbers::UpdateBPMDisplay()
{
	if (!Text_BPM_Numbers) return;

	// Get madness state values
	const float Madness = UserWidgetRef->GetCurrentValue();
	const float Sweat = UserWidgetRef->GetSweetSpotValue();
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
	Text_BPM_Numbers->SetText(FText::FromString(BPMString));
}
