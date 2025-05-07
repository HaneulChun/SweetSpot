// All Rights Reserved by Jason 2025-2026.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpottedObject.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPROJECTBASE_API USpottedObject : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpottedObject();

	bool isFading = false;

	bool spotted = false;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void FadeAway();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	float speed = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	float increaseMadness = 0.1;
};
