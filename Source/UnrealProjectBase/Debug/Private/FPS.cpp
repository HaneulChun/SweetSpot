// All Rights Reserved by SweetSpot 2025-2026.

#include "UnrealProjectBase/Debug/Public/FPS.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

AFPS::AFPS() : DebugMenuRef(nullptr), DebugFPSText(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFPS::BeginPlay()
{
	Super::BeginPlay();

	if (!DebugMenuRef)
	{
	}
}

void AFPS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DebugFPSText)
	{
		float FPS = 1.0f / DeltaTime;
		FString FPSText = FString::Printf(TEXT("FPS: %.1f"), FPS);
		DebugFPSText->SetText(FText::FromString(FPSText));
	}
}
