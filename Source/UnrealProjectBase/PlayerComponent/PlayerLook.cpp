// All Rights Reserved by SweetSpot 2025-2026.


#include "PlayerLook.h"

#include "Camera/CameraComponent.h"

// Sets default values for this component's properties
UPlayerLook::UPlayerLook()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerLook::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerLook::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

AActor* UPlayerLook::LookAtActor()
{
	UCameraComponent* Camera = Cast<UCameraComponent>(GetOwner()->FindComponentByClass<UCameraComponent>());

	if (Camera)
	{
		FVector Start = Camera->GetComponentLocation();
		FVector End = Camera->GetForwardVector() * 1000.0f;

		FHitResult HitResult;
		FCollisionQueryParams Params;

		if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params))
		{
			return Cast<AActor>(HitResult.GetActor());
		}
	}
	return nullptr;
}

