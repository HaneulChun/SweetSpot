// All Rights Reserved by SweetSpot 2025-2026.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "teleport.generated.h"

class UArrowComponent;
class UBoxComponent;

UCLASS()
class UNREALPROJECTBASE_API Ateleport : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Ateleport();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UBoxComponent> triggerBox;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void Teleport(AActor* OtherActor, UArrowComponent* ArrowComponent);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ShowElevatorPart();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void LoadLevel();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UWorld> NextLoopLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UWorld> thisLoopLevel;
public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<Ateleport> teleportTo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UArrowComponent> Arrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UArrowComponent> nextLevelArrow;
};
