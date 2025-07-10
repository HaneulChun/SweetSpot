// All Rights Reserved by SweetSpot 2025-2026.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Elevator.generated.h"

class UFMODEvent;
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
	
	EElevatorPart ElevatorPart;

	UFUNCTION(blueprintCallable)
	void SetChildPart(UChildActorComponent* Component, EElevatorPart Type);
public:	


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AMyTeleport> Teleport;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite ,Category = "Parts")
	TObjectPtr<UChildActorComponent> Switch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite ,Category = "Parts")
	TObjectPtr<UChildActorComponent> Button;

	UPROPERTY(EditAnywhere, BlueprintReadWrite ,Category = "Parts")
	TObjectPtr<UChildActorComponent> Cranck;
	
	UFUNCTION(BlueprintCallable)
	void FixElevator();

	UFUNCTION()
	void ShowElevatorPart(UChildActorComponent* Part);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UFMODEvent> FixElevatorSFX;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Exit();
	virtual void Exit_Implementation();
	

	UFUNCTION()
	void Highlight(EElevatorPart Part);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool TurnOnSwitch = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool TurnOnButton = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool TurnOnCranck = false;
};
