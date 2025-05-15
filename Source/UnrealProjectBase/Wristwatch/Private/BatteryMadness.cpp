// #include "UnrealProjectBase/Wristwatch/Public/BatteryMadness.h"
// #include "UnrealProjectBase/MadnessMeter.h"
// #include "Components/TextBlock.h"
// #include "Blueprint/UserWidget.h"
//
// ABatteryMadness::ABatteryMadness()
// {
// 	PrimaryActorTick.bCanEverTick = true;
// }
//
// void ABatteryMadness::BeginPlay()
// {
// 	Super::BeginPlay();
//
// 	if (BatteryContainerClass)
// 	{
// 		UUserWidget* CreatedWidget = CreateWidget<UUserWidget>(GetWorld(), BatteryContainerClass);
// 		MadnessWidget = Cast<UMadnessMeter>(CreatedWidget);
// 		if (MadnessWidget)
// 		{
// 			MadnessWidget->AddToViewport();
// 		}
// 	}
// }
//
// void ABatteryMadness::Tick(float DeltaTime)
// {
// 	Super::Tick(DeltaTime);
//
// 	TimeSinceLastUpdate += DeltaTime;
// 	if (TimeSinceLastUpdate >= UpdateInterval)
// 	{
// 		UpdateBatteryText();
// 		TimeSinceLastUpdate = 0.0f;
// 	}
// }
//
// // void ABatteryMadness::UpdateBatteryText()
// // {
// // 	if (!MadnessWidget || !MadnessWidget->Text_Battery) return;
// //
// // 	const float Percent = MadnessWidget->GetCurrentValue() * 100.0f;
// // 	const FString PercentText = FString::Printf(TEXT("%.0f%%"), Percent);
// // 	MadnessWidget->Text_Battery->SetText(FText::FromString(PercentText));
// // }
