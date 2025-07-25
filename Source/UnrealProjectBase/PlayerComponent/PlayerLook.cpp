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
	Camera = Cast<UCameraComponent>(GetOwner()->FindComponentByClass<UCameraComponent>());

	CameraLocation = Camera->GetComponentLocation();
	CameraForward = Camera->GetForwardVector();
}


// Called every frame
void UPlayerLook::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

AActor* UPlayerLook::LookAtActor(const TArray<AActor*>& Actors)
{
	// check if there are interactable actors
	if (!Camera || Actors.Num() == 0)
	{
		return nullptr;
	}

	CameraLocation = Camera->GetComponentLocation();
	CameraForward = Camera->GetForwardVector();

	FVector End = CameraLocation + CameraForward * 200.0f;

	FHitResult HitResult;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(MyTrace), true);

	// ray tracing
	if (GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, End, ECC_Visibility, Params))
	{
		if (TObjectPtr<AActor> HitActor = HitResult.GetActor())
		{
			for (AActor* Actor : Actors)
			{
				if (HitActor == Actor)
				{
					// return the actor that was hit
					return HitActor;
				}
			}
		}
	}
	
	BestActor = nullptr;
	float BestDot = 0.97f;

	// dot product to see which actor is the best actor
	for (AActor* Actor : Actors)
	{
		if (!Actor) continue;

		float Actordistance = FVector::Distance(CameraLocation, Actor->GetActorLocation());
		if (Actordistance > 250) continue;
		
		FVector DirectionToActor = (Actor->GetActorLocation() - CameraLocation).GetSafeNormal();
		float Dot = FVector::DotProduct(CameraForward, DirectionToActor);

		if (Dot > BestDot)
		{
			BestDot = Dot;
			BestActor = Actor;
		}
	}
	if (BestActor)
	{
		return BestActor;
	}
	
	return nullptr;
}


