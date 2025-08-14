// All Rights Reserved by SweetSpot 2025-2026.


#include "SweetSpotCharacter.h"

// Sets default values
ASweetSpotCharacter::ASweetSpotCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


bool ASweetSpotCharacter::IsEditor()
{
	if (GetWorld() && GetWorld()->WorldType == EWorldType::PIE)
	{
		return true;
	}
	return false;
}

// Called to bind functionality to input
void ASweetSpotCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

