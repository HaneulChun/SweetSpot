// All Rights Reserved by Jason 2025-2026.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerVision.generated.h"


class UCameraComponent;
class UMeshComponent;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPROJECTBASE_API UPlayerVision : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerVision();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<AActor*> ActorArray;

	UPROPERTY(blueprintReadWrite)
	bool isFocusing = false;

	UPROPERTY(BlueprintReadOnly)
	UCameraComponent* PlayerCamera;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetActorArray();
private:
	int32 FrameCounter = 0;	
};
