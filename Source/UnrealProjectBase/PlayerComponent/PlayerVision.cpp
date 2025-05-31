// All Rights Reserved by Jason 2025-2026.


#include "PlayerVision.h"
#include "UnrealProjectBase/Actors/SpottedObject.h"
#include "EngineUtils.h"
#include "UnrealProjectBase/Actors/BigEye.h"
#include "Math/Vector.h"
#include "Camera/CameraComponent.h"

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

	SetActorArray();

	PlayerCamera = GetOwner()->FindComponentByClass<UCameraComponent>();

	PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerPawn = PlayerController->GetPawn();


	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UPlayerVision::LookForEye, 0.2f, true);
	
	GetWorld()->GetTimerManager().SetTimer(BigTimerHandle, this, &UPlayerVision::LookForBigEye, 0.1f, true);
}


// Called every frame
void UPlayerVision::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPlayerVision::LookForEye()
{
	PlayerLocation = PlayerPawn->GetActorLocation();

	// check if the eye was recently rendered
	for (AActor* Actor : eyeArray)
	{
		if (Actor)
		{
			if (Actor && Actor->WasRecentlyRendered(0.1f))
			{
				FVector Center = eyeMeshArray[EyeIndex]->Bounds.Origin;
				float Radius = eyeMeshArray[EyeIndex]->Bounds.SphereRadius;

				// set points to check if the player can see the object
				TArray<FVector> PointsToCheck = {
					Center,
					Center + FVector(Radius, 0, 0),
					Center + FVector(-Radius, 0, 0),
					Center + FVector(0, Radius, 0),
					Center + FVector(0, -Radius, 0),
					Center + FVector(0, 0, Radius),
					Center + FVector(0, 0, -Radius)
				};

				// check if there is a wall between player and point
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
						Params);

					// if see actor make it fade away
					if (!bHit || HitResult.GetActor() == Actor)
					{
						// normal eyeball fading
						if (USpottedObject* object = Cast<USpottedObject>(Actor->FindComponentByClass<USpottedObject>()))
						{
							object->FadeAway();
						}
						break; 
					}
				}
			}
		}
		EyeIndex++;
	}
	EyeIndex = 0;
}

void UPlayerVision::LookForBigEye()
{
	PlayerLocation = PlayerPawn->GetActorLocation();
	
	// check if the eye was recently rendered
	for (AActor* Actor : bigEyeArray)
	{
		if (Actor)
		{
			if (Actor && Actor->WasRecentlyRendered(0.1f))
			{
				FVector Center = bigEyeMeshArray[bigEyeIndex]->Bounds.Origin;
				float Radius = bigEyeMeshArray[bigEyeIndex]->Bounds.SphereRadius;
	
	
				// set points to check if the player can see the object
				TArray<FVector> PointsToCheck = {
					Center,
					Center + FVector(Radius, 0, 0),
					Center + FVector(-Radius, 0, 0),
					Center + FVector(0, Radius, 0),
					Center + FVector(0, -Radius, 0),
					Center + FVector(0, 0, Radius),
					Center + FVector(0, 0, -Radius)
				};
	
	
				// check if there is a wall between player and point
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
						Params);
	
	
					// if see actor make it fade away
					if (!bHit || HitResult.GetActor() == Actor)
					{
						// big eyeball
						if (ABigEye* object2 = Cast<ABigEye>(Actor))
						{
							// dot product 
							FVector playerForward = PlayerCamera->GetForwardVector();
							FVector objectToLookAt = (Actor->GetActorLocation() - PlayerCamera->GetComponentLocation()).GetSafeNormal();
							float Dot = FVector::DotProduct(playerForward, objectToLookAt);
	
	
							// check if player is looking at big eye
							if (Dot > 0.99f)
							{
								// Direction *away* from object
								FVector LookAwayDirection = -objectToLookAt;
								
								FRotator CurrentRotation = PlayerController->GetControlRotation();
								FRotator TargetRotation = LookAwayDirection.Rotation();
								
								// Interpolate rotation
								FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), IntensitySpeed);
								PlayerController->SetControlRotation(NewRotation);
								
								// if player is focusing fade the object 
								if (isFocusing)
								{
									object2->FadeAway();
								}
								object2->IncreaseMadness();
							}
						}
						break; 
					}
				}
			}
		}
		bigEyeIndex++;
	}
	bigEyeIndex = 0;
}

void UPlayerVision::SetActorArray()
{
	eyeArray.Empty();
	eyeMeshArray.Empty();
	bigEyeArray.Empty();
	bigEyeMeshArray.Empty();

	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		AActor* Actor = *ActorItr;
		
		if (Actor->Tags.Contains("SeeMe"))
		{
			eyeArray.Add(Actor);
			eyeMeshArray.Add(Actor->FindComponentByClass<UMeshComponent>());
		}
		else if (Actor->Tags.Contains("BigEye"))
		{
			bigEyeArray.Add(Actor);
			bigEyeMeshArray.Add(Actor->FindComponentByClass<UMeshComponent>());
		}
	}
}
