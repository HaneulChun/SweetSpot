// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "MadnessMeterWidget.h"

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MadnessMeterWidget)
	{
		UMadnessMeterWidget* WidgetInstance = CreateWidget<UMadnessMeterWidget>(GetWorld(), MadnessMeterWidget);
		if (WidgetInstance)
		{
			WidgetInstance->AddToViewport();
		}
	}
}
