// All Rights Reserved by SweetSpot 2025-2026.


#include "SweetSpotCharacter.h"

// Sets default values
ASweetSpotCharacter::ASweetSpotCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASweetSpotCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASweetSpotCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASweetSpotCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

