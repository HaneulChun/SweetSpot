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


	CurrentTimer = Timer;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APlayerHud::UpdateTimer, 1, true);

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
			}
		}
	}
}

void APlayerHud::UpdateTimer()
{
	CurrentTimer -= 1;
	int32 Minutes = FMath::FloorToInt(CurrentTimer / 60);  
	int32 Seconds = FMath::Fmod(CurrentTimer, 60); 
	timerText = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
	if (CurrentTimer <= 0)
	{
		timerText = "End";
		
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			APawn* Player = PlayerController->GetPawn();
			if (Player)
			{
				for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
				{
					AActor* Actor = *ActorItr;
		
					if (Actor->Tags.Contains("Spawn"))
					{
						Player->SetActorLocation(Actor->GetActorLocation());
					}
				}
			}
		}
		CurrentTimer = Timer;
	}
}

void APlayerHud::DrawHUD()
{
	Super::DrawHUD();
	
	FCanvasTextItem TextItem(FVector2D(20, 40), FText::FromString(timerText), GEngine->GetLargeFont(), FLinearColor::White);
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
