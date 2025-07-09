// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FMODEvent.h"
#include "PlayerHud.generated.h"

class UPopUpWidget;
class UMyUserWidget;
UCLASS()
class UNREALPROJECTBASE_API APlayerHud : public AHUD
{
	GENERATED_BODY()

protected:
	FTimerHandle TimerHandle;
	
	virtual void BeginPlay() override;

public:
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UMyUserWidget> WidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UPopUpWidget> PopUpWidgetClass;

	
	UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMyUserWidget> CurrentWidget;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPopUpWidget> PopUpWidget;

	
	UFUNCTION(BlueprintCallable, Category = "UI")
	UMyUserWidget* GetMadnessMeterWidget() const;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	TObjectPtr<UFMODEvent> FullyMadSFX;

	UPROPERTY(EditAnywhere, BluePrintReadWrite)
	float sweetSpot = 0.4;

	UPROPERTY(EditAnywhere, BluePrintReadWrite)
	float mad = 0.6;
};
