// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MadnessMeterWidget.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EMadnessState : uint8
{
	Sane UMETA(DisplayName = "Sane"),
	Mad UMETA(DisplayName = "Mad"),
	SweatSpot UMETA(DisplayName = "Sweat Spot"),
	Dead UMETA(DisplayName = "Dead")
};

UCLASS()
class UNREALPROJECTBASE_API UMadnessMeterWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Madness")
	EMadnessState CurrentState;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	UUserWidget* CurrentWidget;
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	UUserWidget* GetWidget() const;
};
