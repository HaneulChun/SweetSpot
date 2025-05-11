// All Rights Reserved by SweetSpot 2025-2026.

#include "UnrealProjectBase/Wristwatch/Wristwatch_Time.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Misc/DateTime.h"

AWristwatch_Time::AWristwatch_Time()
{
	PrimaryActorTick.bCanEverTick = true;

	// Optional: Customize text component settings here
	GetTextRender()->SetHorizontalAlignment(EHTA_Center);
	GetTextRender()->SetVerticalAlignment(EVRTA_TextCenter);
	GetTextRender()->SetTextRenderColor(FColor::Cyan);
	GetTextRender()->SetWorldSize(25.f);
}

void AWristwatch_Time::BeginPlay()
{
	Super::BeginPlay();
	UpdateTimeDisplay();
}

void AWristwatch_Time::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeSinceLastUpdate += DeltaTime;
	if (TimeSinceLastUpdate >= TimeUpdateInterval)
	{
		UpdateTimeDisplay();
		TimeSinceLastUpdate = 0.0f;
	}
}

void AWristwatch_Time::UpdateTimeDisplay() const
{
	const FDateTime Now = FDateTime::Now();
	const FString TimeString = Now.ToString(TEXT("%H:%M:%S"));
	GetTextRender()->SetText(FText::FromString(TimeString));
}
