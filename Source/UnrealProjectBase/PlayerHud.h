// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FMODEvent.h"
#include "PlayerHud.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECTBASE_API APlayerHud : public AHUD
{
	GENERATED_BODY()

protected:
	FTimerHandle TimerHandle;
	
	virtual void BeginPlay() override;

	virtual void DrawHUD() override;
	
public:
	APlayerHud();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	FString Text = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UUserWidget* CurrentWidget;
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	UUserWidget* GetWidget() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	UFMODEvent* FullyMadSFX;
	

	UPROPERTY(EditAnywhere, BluePrintReadWrite)
	float sweatSpot = 0.4;

	UPROPERTY(EditAnywhere, BluePrintReadWrite)
	float mad = 0.6;
	
	UPROPERTY(EditAnywhere, BluePrintReadWrite)
	TArray<UMaterialInterface*> Material;

	UFUNCTION()
	void emptyText();

	UFUNCTION()
	void SetText(FString setText);
};
