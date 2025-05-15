// #pragma once
//
// #include "CoreMinimal.h"
// #include "Engine/TextRenderActor.h"
// #include "BatteryMadness.generated.h"
//
// UCLASS()
// class UNREALPROJECTBASE_API ABatteryMadness : public ATextRenderActor
// {
// 	GENERATED_BODY()
//
// public:
// 	ABatteryMadness();
//
// protected:
// 	virtual void BeginPlay() override;
// 	virtual void Tick(float DeltaTime) override;
//
// private:
// 	// UMG widget class reference (set in editor)
// 	UPROPERTY(EditAnywhere, Category = "UI")
// 	TSubclassOf<class UUserWidget> BatteryContainerClass;
//
// 	// Widget instance and casted reference
// 	UPROPERTY()
// 	class UMadnessMeter* MadnessWidget;
//
// 	// Battery UI text updater
// 	void UpdateBatteryText();
//
// 	UPROPERTY(EditAnywhere, Category = "UI")
// 	float UpdateInterval = 0.25f;
//
// 	float TimeSinceLastUpdate = 0.0f;
// };
