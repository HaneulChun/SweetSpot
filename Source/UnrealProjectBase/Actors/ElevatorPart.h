// All Rights Reserved by SweetSpot 2025-2026.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ElevatorPart.generated.h"

enum class EElevatorPart : uint8;

UCLASS()
class UNREALPROJECTBASE_API AElevatorPart : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AElevatorPart();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EElevatorPart ElevatorPart;
};
