// All Rights Reserved by SweetSpot 2025-2026.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TextMessageBox.generated.h"

/**
 * 
 */
class UTextBlock;
class UUserWidget;

UCLASS()
class UNREALPROJECTBASE_API ATextMessageBox : public AActor
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	ATextMessageBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	FTimerHandle MessageClearTimerHandle;
	void ClearMessageText();
	bool bClearingScheduled;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Reference to the desired widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UUserWidget* WBP_MessageBox_Container;

	// Reference to the desired text block
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UTextBlock* Text_MessageBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FString MessageToDisplay;
};