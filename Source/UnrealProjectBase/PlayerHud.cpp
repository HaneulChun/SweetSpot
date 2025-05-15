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
		CurrentWidget = CreateWidget<UMyUserWidget>(GetWorld(), WidgetClass);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
			
			CurrentWidget->sweatSpot = sweatSpot;
			CurrentWidget->mad = mad;
				
			CurrentWidget->SetMaterial(Material);

			if (FullyMadSFX)
			{
				CurrentWidget->FullyMadSFX = FullyMadSFX;
			}
		}
	}
	Text = TEXT("");
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APlayerHud::emptyText, 0.1, false);
}

void APlayerHud::DrawHUD()
{
	Super::DrawHUD();
	
	FCanvasTextItem TextItem(FVector2D(500, 40), FText::FromString(Text), GEngine->GetLargeFont(), FLinearColor::White);
	TextItem.Scale = FVector2D(1.5f, 1.5f);
	
	Canvas->DrawItem(TextItem);
}

UMyUserWidget* APlayerHud::GetWidget() const
{
	return CurrentWidget;
}

void APlayerHud::emptyText()
{
	Text = TEXT("");
}

void APlayerHud::SetText(FString setText)
{
	Text = setText;
}
