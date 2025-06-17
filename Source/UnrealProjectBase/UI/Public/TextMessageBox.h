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
class UNREALPROJECTBASE_API UATextMessageBox : public UUserWidget
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	UATextMessageBox();

protected:
	// Called when the game starts or when spawned
	virtual void NativeConstruct() override;

public:	
	// Called every frame
	virtual void NativeTick(float DeltaTime) override;

	// Reference to the desired widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UUserWidget* WBP_MessageBox_Container;

	// Reference to the desired text block
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UTextBlock* Text_MessageBox;
};