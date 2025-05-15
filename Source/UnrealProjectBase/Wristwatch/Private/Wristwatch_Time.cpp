// All Rights Reserved by SweetSpot 2025-2026.

#include "UnrealProjectBase/Wristwatch/Public/Wristwatch_Time.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/DateTime.h"

AWristwatch_Time::AWristwatch_Time()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWristwatch_Time::BeginPlay()
{
	Super::BeginPlay();

	if (WatchScreenWidgetClass)
	{
		WatchScreenWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), WatchScreenWidgetClass);
		if (WatchScreenWidgetInstance)
		{
			WatchScreenWidgetInstance->AddToViewport();
		}
	}
}

void AWristwatch_Time::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeSinceLastUpdate += DeltaTime;
	if (TimeSinceLastUpdate >= TimeUpdateInterval)
	{
		UpdateTimeInUI();
		TimeSinceLastUpdate = 0.0f;
	}
}

void AWristwatch_Time::UpdateTimeInUI()
{
	if (!WatchScreenWidgetInstance) return;

	// Get the current system time as a formatted string (HH:MM:SS)
	const FDateTime Now = FDateTime::Now();
	const FString TimeString = Now.ToString(TEXT("%H:%M:%S"));

	// Find the nested Time_Container widget inside WatchScreenWidgetInstance
	UWidget* TimeContainerWidget = WatchScreenWidgetInstance->GetWidgetFromName(TEXT("Time_Container"));
	if (!TimeContainerWidget) return;

	// Cast to UUserWidget because Time_Container is a widget container
	UUserWidget* TimeContainerUserWidget = Cast<UUserWidget>(TimeContainerWidget);
	if (!TimeContainerUserWidget) return;

	// Find the TextBlock named Widget_Time inside Time_Container
	UTextBlock* TimeTextBlock = Cast<UTextBlock>(TimeContainerUserWidget->GetWidgetFromName(TEXT("Widget_Time")));
	if (TimeTextBlock)
	{
		TimeTextBlock->SetText(FText::FromString(TimeString));
	}
}
