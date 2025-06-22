// All Rights Reserved by Jason 2025-2026.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpottedObject.generated.h"


class UMyUserWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class UNREALPROJECTBASE_API USpottedObject : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpottedObject();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isClosingAnim = false;
	
	UPROPERTY()
	TObjectPtr<UMyUserWidget> widget;
	
	FTransform startTransform;

	FTimerHandle TimerHandle;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float restoreMadnessValue = 0.1;
public:	

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void FadeAway();
	virtual void FadeAway_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ResetPosition();
	virtual void ResetPosition_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void LookAtPlayer();
	virtual void LookAtPlayer_Implementation();
	
	UFUNCTION()
	void IncreaseMadness();

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	float speed = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	float increaseMadnessAmount = 0.004;

	UPROPERTY(EditAnywhere, Category = "Property")
	int focusedLookTicks = 20;

	int count = 0;
};
