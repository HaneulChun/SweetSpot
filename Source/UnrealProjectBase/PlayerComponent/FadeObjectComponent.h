// All Rights Reserved by SweetSpot 2025-2026.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FadeObjectComponent.generated.h"


class UMyUserWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class UNREALPROJECTBASE_API UFadeObjectComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFadeObjectComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY()
	TObjectPtr<UMyUserWidget> widget;
public:	
	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<AActor>> SaneActors;
	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<AActor>> SweetActors;
	UPROPERTY()
	TObjectPtr<AActor> spawnPoint;

	UFUNCTION(BlueprintImplementableEvent)
	void Fade(float saneTime, float saneStartValue, float sweetTime, float sweetStartValue);

	UFUNCTION(BlueprintCallable)
	void StartLoop();
};
