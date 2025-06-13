// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FMODEvent.h"
#include "PlayerHud.generated.h"

/**
 * 
 */
class UMyUserWidget;
UCLASS()
class UNREALPROJECTBASE_API APlayerHud : public AHUD
{
	GENERATED_BODY()

protected:
	FTimerHandle TimerHandle;
	
	virtual void BeginPlay() override;

	virtual void DrawHUD() override;

	bool isShowImage = false;
public:

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	FString Text = "";

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	FString GotoText = "";
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UMyUserWidget> WidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMyUserWidget> CurrentWidget;
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	UMyUserWidget* GetMadnessMeterWidget() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	TObjectPtr<UFMODEvent> FullyMadSFX;
	

	UPROPERTY(EditAnywhere, BluePrintReadWrite)
	float sweetSpot = 0.4;

	UPROPERTY(EditAnywhere, BluePrintReadWrite)
	float mad = 0.6;
	
	UPROPERTY(EditAnywhere, BluePrintReadWrite)
	TArray<TObjectPtr<UMaterialInterface>> Material;

	UFUNCTION(BlueprintCallable)
	void SetTextTodo(FString setText);

	UFUNCTION(BlueprintCallable)
	void SetText(FString setText);
};
