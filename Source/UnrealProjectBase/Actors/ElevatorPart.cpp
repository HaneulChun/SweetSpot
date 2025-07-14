// All Rights Reserved by SweetSpot 2025-2026.


#include "ElevatorPart.h"

// Sets default values
AElevatorPart::AElevatorPart()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AElevatorPart::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AElevatorPart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

