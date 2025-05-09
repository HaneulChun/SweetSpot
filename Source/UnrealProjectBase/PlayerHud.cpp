// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHud.h"

#include "CanvasItem.h"
#include "EngineUtils.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Canvas.h"
#include "MyUserWidget.h"

void APlayerHud::BeginPlay()
{
	Super::BeginPlay();

	if (WidgetClass)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
			if (UMyUserWidget* widget = Cast<UMyUserWidget>(CurrentWidget))
			{
				widget->sweatSpot = sweatSpot;
				widget->mad = mad;
				
				widget->SetMaterial(Material);

				if (FullyMadSFX)
				{
					widget->FullyMadSFX = FullyMadSFX;
				}
			}
		}
	}
	Text = TEXT("E to Interact with object");
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APlayerHud::emptyText, 0.1, false);
}

void APlayerHud::DrawHUD()
{
	Super::DrawHUD();
	
	FCanvasTextItem TextItem(FVector2D(500, 40), FText::FromString(Text), GEngine->GetLargeFont(), FLinearColor::White);
	TextItem.Scale = FVector2D(1.5f, 1.5f);
	
	Canvas->DrawItem(TextItem);
}


APlayerHud::APlayerHud()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetObj(TEXT("/All/Game/Jason/UI/MadnessBar"));
	if (WidgetObj.Succeeded())
	{
		WidgetClass = WidgetObj.Class;
	}

	CurrentWidget = nullptr;
}

UUserWidget* APlayerHud::GetWidget() const
{
	return CurrentWidget;
}

void APlayerHud::emptyText()
{
	Text = TEXT("E to Interact with object");
}

void APlayerHud::SetText(FString setText)
{
	Text = setText;
}
