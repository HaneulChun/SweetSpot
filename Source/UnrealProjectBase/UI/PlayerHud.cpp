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

	// set the madness meter
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
	
	// set the text on sceen (only for prototype)
	FCanvasTextItem TextItem(FVector2D(500, 40), FText::FromString(Text), GEngine->GetLargeFont(), FLinearColor::Red);
	TextItem.Scale = FVector2D(2.5f, 2.5f);
	
	FCanvasTextItem TextItemGoto(FVector2D(1000, 40), FText::FromString(GotoText), GEngine->GetLargeFont(), FLinearColor::Red);
	TextItemGoto.Scale = FVector2D(2.5f, 2.5f);
	
	Canvas->DrawItem(TextItem);
	Canvas->DrawItem(TextItemGoto);
	
	if (MyTexture && isShowImage)
	{
		FVector2D ImageSize(128, 128);
		FVector2D ImagePosition(Canvas->ClipX - ImageSize.X, Canvas->ClipY - ImageSize.Y);
	
		FCanvasTileItem TileItem(ImagePosition, MyTexture->GetResource(), ImageSize, FLinearColor::White);
		TileItem.BlendMode = SE_BLEND_Translucent;
		
		Canvas->DrawItem(TileItem);
	
		
		FVector2D position = ImagePosition - FVector2D(ImageSize.X, -70);
		
		FCanvasTextItem LMBText(position, FText::FromString(ChocoleteText), GEngine->GetLargeFont(), FLinearColor::Red);
		LMBText.Scale = FVector2D(2.5f, 2.5f);
		
		Canvas->DrawItem(LMBText);
	}
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

void APlayerHud::SetTextLMB(bool img)
{
	isShowImage = img;
}
