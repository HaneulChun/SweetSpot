// All Rights Reserved by Jason 2025-2026.


#include "PlayerVision.h"
#include "SpottedObject.h"
#include "EngineUtils.h"
#include "PlayerHud.h"
#include "MyUserWidget.h"

// Sets default values for this component's properties
UPlayerVision::UPlayerVision()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerVision::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UPlayerVision::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FrameCounter++;
	if (FrameCounter % 10 == 0)
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		APawn* PlayerPawn = PlayerController->GetPawn();

		if (!PlayerPawn)
			return;
		
		FVector PlayerLocation = PlayerPawn->GetActorLocation();
		
		for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			AActor* Actor = *ActorItr;
		
			if (Actor->Tags.Contains("SeeMe"))
			{
				UMeshComponent* MeshComp = Actor->FindComponentByClass<UMeshComponent>();
				if (MeshComp && MeshComp->WasRecentlyRendered(0.1f))
				{
					FVector Center = MeshComp->Bounds.Origin;
					float Radius = MeshComp->Bounds.SphereRadius;

					TArray<FVector> PointsToCheck = {
						Center,
						Center + FVector(Radius, 0, 0),
						Center + FVector(-Radius, 0, 0),
						Center + FVector(0, Radius, 0),
						Center + FVector(0, -Radius, 0),
						Center + FVector(0, 0, Radius),
						Center + FVector(0, 0, -Radius)
					};
					
					for (const FVector& Point : PointsToCheck)
					{
						FHitResult HitResult;
						FCollisionQueryParams Params;
						Params.AddIgnoredActor(PlayerPawn);

						bool bHit = GetWorld()->LineTraceSingleByChannel(
							HitResult,
							PlayerLocation,
							Point,
							ECC_Visibility,
							Params
						);

						if (!bHit || HitResult.GetActor() == Actor)
						{
							if (USpottedObject* object = Cast<USpottedObject>(Actor->FindComponentByClass<USpottedObject>()))
							{
								object->FadeAway();
							}
							break; 
						}
					}
				}
			}
		}
	}
}