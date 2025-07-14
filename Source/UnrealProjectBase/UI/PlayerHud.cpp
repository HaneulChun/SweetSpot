// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHud.h"

#include "Blueprint/UserWidget.h"
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

UMyUserWidget* APlayerHud::GetMadnessMeterWidget() const
{
	return CurrentWidget;
}