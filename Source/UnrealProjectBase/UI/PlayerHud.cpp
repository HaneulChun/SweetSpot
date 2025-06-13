// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHud.h"

#include "CanvasItem.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Canvas.h"
#include "MyUserWidget.h"
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
			
			CurrentWidget->sweatSpot = sweetSpot;
			CurrentWidget->mad = mad;
				
			CurrentWidget->SetMaterial(Material);

			if (FullyMadSFX)
			{
				CurrentWidget->FullyMadSFX = FullyMadSFX;
			}
		}
	}
	Text = TEXT("");
}

void APlayerHud::DrawHUD()
{
	Super::DrawHUD();
	
	// set the text on sceen (only for prototype)
	FCanvasTextItem TextItem(FVector2D(500, 40), FText::FromString(Text), GEngine->GetLargeFont(), FLinearColor::Red);
	TextItem.Scale = FVector2D(2.5f, 2.5f);
	
	FCanvasTextItem TextItemGoto(FVector2D(1000, 40), FText::FromString(GotoText), GEngine->GetLargeFont(), FLinearColor::Red);
	TextItemGoto.Scale = FVector2D(2.5f, 2.5f);
	
	Canvas->DrawItem(TextItem);
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

void APlayerHud::SetText(FString setText)
{
	Text = setText;
}