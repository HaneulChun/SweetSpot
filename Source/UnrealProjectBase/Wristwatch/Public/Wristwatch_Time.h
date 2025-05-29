// All Rights Reserved by SweetSpot 2025-2026.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Wristwatch_Time.generated.h"

class UUserWidget;
class UTextBlock;
class UWidget;

UCLASS()
class UNREALPROJECTBASE_API AWristwatch_Time : public AActor
{
	GENERATED_BODY()

public:
	AWristwatch_Time();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Interval in seconds between time updates
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
	float TimeUpdateInterval = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UObject* Time_Container;

private:
	// Accumulator to track time elapsed since last update
	float TimeSinceLastUpdate = 0.0f;

	// The main watch screen widget (BP_Watch_Screen)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> WatchScreenWidgetClass;

	// Instance of the watch screen widget
	UUserWidget* WatchScreenWidgetInstance = nullptr;

	// Updates the text of Widget_Time inside Time_Container widget
	void UpdateTimeInUI();
};
