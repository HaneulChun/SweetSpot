// Fill out your copyright notice in the Description page of Project Settings.


#include "MadnessMeterWidget.h"

void UMadnessMeterWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (WidgetClass)
	{
		CurrentWidget = CreateWidget<UUserWidget>(this, WidgetClass);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "MadnessMeterWidget::NativeConstruct");
}

void UMadnessMeterWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

UUserWidget* UMadnessMeterWidget::GetWidget() const
{
	return CurrentWidget;
}
