// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHud.h"

#include "CanvasItem.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Canvas.h"
#include "MyUserWidget.h"
#include "PopUpWidget.h"
//WidgetClass
void APlayerHud::BeginPlay()
{
	Super::BeginPlay();

	// set the madness meter
	if (WidgetClass)
	{
		CurrentWidget = CreateWidget<UMyUserWidget>(GetWorld(), WidgetClass);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
			
			CurrentWidget->sweetSpot = sweetSpot;
			CurrentWidget->mad = mad;

			if (FullyMadSFX)
			{
				CurrentWidget->FullyMadSFX = FullyMadSFX;
			}
		}
	}

	// set up popUp Widget
	if (PopUpWidgetClass)
	{
		PopUpWidget = CreateWidget<UPopUpWidget>(GetWorld(), PopUpWidgetClass);
		if (PopUpWidget)
		{
			PopUpWidget->AddToViewport();
		}
	}
}

void APlayerHud::DrawHUD()
{
	Super::DrawHUD();
	FCanvasTextItem TextItemGoto(FVector2D(1000, 40), FText::FromString(GotoText), GEngine->GetLargeFont(), FLinearColor::Red);
	TextItemGoto.Scale = FVector2D(2.5f, 2.5f);
	
	Canvas->DrawItem(TextItemGoto);
}

UMyUserWidget* APlayerHud::GetMadnessMeterWidget() const
{
	return CurrentWidget;
}


void APlayerHud::SetTextTodo(FString setText)
{
	GotoText = setText;
}