// All Rights Reserved by SweetSpot 2025-2026.


#include "PlayerInventory.h"
#include "UnrealProjectBase/UI/PlayerHud.h"

// Sets default values for this component's properties
UPlayerInventory::UPlayerInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UPlayerInventory::GetElevatorPart(EElevatorPart newElevatorPart)
{
	ElevatorPart = newElevatorPart;
}

void UPlayerInventory::UseElevatorPart()
{
}

