// All Rights Reserved by SweetSpot 2025-2026.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerInventory.generated.h"


UENUM(BlueprintType)
enum class EElevatorPart : uint8
{
	None UMETA(DisplayName = "None"),
	Switch UMETA(DisplayName = "Switch"),
	Button UMETA(DisplayName = "Button"),
	Cranck UMETA(DisplayName = "Cranck")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPROJECTBASE_API UPlayerInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerInventory();

public:	
	UFUNCTION(BlueprintCallable)
	void GetElevatorPart(EElevatorPart newElevatorPart);

	UFUNCTION(BlueprintCallable)
	void UseElevatorPart();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Madness")
	EElevatorPart ElevatorPart = EElevatorPart::None;
};
