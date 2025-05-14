// All Rights Reserved by SweetSpot 2025-2026.


#include "PlayerInventory.h"

// Sets default values for this component's properties
UPlayerInventory::UPlayerInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UPlayerInventory::AddChocolate()
{
	if (currentChocolate < 6)
	{
		currentChocolate++;
		return true;
	}
	return false;
}

bool UPlayerInventory::EatChocolate()
{
	if (currentChocolate > 0)
	{
		currentChocolate--;
		return true;
	}
	return false;
}

void UPlayerInventory::GetElevatorPart(EElevatorPart newElevatorPart)
{
	ElevatorPart = newElevatorPart;
}

void UPlayerInventory::UseElevatorPart()
{
}

