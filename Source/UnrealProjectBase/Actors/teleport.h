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
	UBoxComponent* triggerBox;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void Teleport(AActor* OtherActor);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ShowElevatorPart();
	
public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<Ateleport> teleportTo;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UArrowComponent> Arrow;
};
