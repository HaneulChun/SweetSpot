// All Rights Reserved by SweetSpot 2025-2026.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Elevator.generated.h"

enum class EElevatorPart : uint8;
class AMyTeleport;
class UBoxComponent;
UCLASS()
class UNREALPROJECTBASE_API AElevator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AElevator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	EElevatorPart ElevatorPart;
public:	


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AMyTeleport> Teleport;
	
	UPROPERTY(VisibleAnywhere, Category = "Parts")
	UChildActorComponent* Switch;

	UPROPERTY(VisibleAnywhere, Category = "Parts")
	UChildActorComponent* Button;

	UPROPERTY(VisibleAnywhere, Category = "Parts")
	UChildActorComponent* Cranck;
	
	UFUNCTION(BlueprintCallable)
	void FixElevator();
};
