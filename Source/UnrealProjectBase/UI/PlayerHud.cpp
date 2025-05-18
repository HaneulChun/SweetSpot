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
}

void APlayerHud::DrawHUD()
{
	Super::DrawHUD();
	
	FCanvasTextItem TextItem(FVector2D(500, 40), FText::FromString(Text), GEngine->GetLargeFont(), FLinearColor::Red);
	TextItem.Scale = FVector2D(2.5f, 2.5f);

	FCanvasTextItem TextItemGoto(FVector2D(1000, 40), FText::FromString(GotoText), GEngine->GetLargeFont(), FLinearColor::Red);
	TextItemGoto.Scale = FVector2D(2.5f, 2.5f);
	
	Canvas->DrawItem(TextItem);
	Canvas->DrawItem(TextItemGoto);
}

UMyUserWidget* APlayerHud::GetWidget() const
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
