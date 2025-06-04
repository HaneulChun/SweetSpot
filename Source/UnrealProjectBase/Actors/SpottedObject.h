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

	UPROPERTY(BlueprintReadWrite)
	bool isFading = false;

	UPROPERTY(BlueprintReadWrite)
	bool spotted = false;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<UMyUserWidget> widget;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Fade")
	void FadeAway();
	virtual void FadeAway_Implementation();

	UFUNCTION()
	void IncreasePlayerMadness();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	float speed = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	float increaseMadness = 0.02;
};
