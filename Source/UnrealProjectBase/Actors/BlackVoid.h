// All Rights Reserved by SweetSpot 2025-2026.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlackVoid.generated.h"

class UBoxComponent;

UCLASS()
class UNREALPROJECTBASE_API ABlackVoid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlackVoid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> start;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> end;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> blackVoid;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	TObjectPtr<UBoxComponent> triggerBox;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void StartVoid();
private:
	UPROPERTY(EditAnywhere)
	float MoveDuration = 4.0f;
	
	float ElapsedTime = 0.0f;
};
