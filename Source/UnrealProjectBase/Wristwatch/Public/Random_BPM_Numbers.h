// All Rights Reserved by SweetSpot 2025-2026.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextBlock.h"
#include "UnrealProjectBase/MyUserWidget.h"
#include "Random_BPM_Numbers.generated.h"

UCLASS()
class UNREALPROJECTBASE_API ARandom_BPM_Numbers : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ARandom_BPM_Numbers();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	UMyUserWidget* UserWidgetRef;

	UPROPERTY()
	UTextBlock* BPMText;

	void UpdateBPMDisplay();
};
