// All Rights Reserved by SweetSpot 2025-2026.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPS.generated.h"

class UTextBlock;
class UUserWidget;

UCLASS()
class UNREALPROJECTBASE_API AFPS : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPS();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Reference to the debug menu widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug Menu")
	UUserWidget* DebugMenuRef;

	// Reference to the FPS text block
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug Menu")
	UTextBlock* DebugFPSText;
};
