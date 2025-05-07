// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

class UMadnessMeterWidget;
UCLASS()
class UNREALPROJECTBASE_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
private:
	virtual void BeginPlay() override;
	
public:
	// Madness Meter
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MadnessMeter", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UMadnessMeterWidget> MadnessMeterWidget;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "MadnessMeter")
	TArray<UMaterialInterface*> Material;
	
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "MadnessMeter")
	float sweatSpot = 0.4;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "MadnessMeter")
	float mad = 0.6;
};
