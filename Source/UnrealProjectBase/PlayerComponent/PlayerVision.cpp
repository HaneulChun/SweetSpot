// All Rights Reserved by Jason 2025-2026.


#include "PlayerVision.h"
#include "UnrealProjectBase/Actors/SpottedObject.h"
#include "EngineUtils.h"
#include "UnrealProjectBase/Actors/BigEye.h"
#include "Math/Vector.h"
#include "Camera/CameraComponent.h"
#include "UnrealProjectBase/Actors/Eye.h"
#include "UnrealProjectBase/Actors/TentacleWall.h"
#include "Math/UnrealMathUtility.h"

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

	GetWorld()->GetTimerManager().SetTimer(tenticalTimerHandle, this, &UPlayerVision::Interval, tenticalCheckInterval, true);
}


float UPlayerVision::DotProduct(const FVector &TargetVector)
{
	FVector playerForward = PlayerCamera->GetForwardVector();
	FVector objectToLookAt = (TargetVector - PlayerCamera->GetComponentLocation()).GetSafeNormal();
	float Dot = FVector::DotProduct(playerForward, objectToLookAt);
	
	return Dot;
}

void UPlayerVision::Interval()
{
	LookForTentacleWall();
	LookForEye();
	LookForBigEye();
}


void UPlayerVision::LookForTentacleWall()
{
	if (!isFocusing) return;
	
	PlayerLocation = PlayerCamera->GetComponentLocation();

	// check if the eye was recently rendered
	for (TObjectPtr<AActor> Actor : tenticalArray)
	{
		if (IsValid(Actor) && !Actor->IsPendingKillPending())
		{
			FVector ActorLocation = Actor->GetActorLocation(); 
			float dProduct = DotProduct(ActorLocation);
			if (dProduct > 0.54)
			{
				FVector bottom = tenticalMeshArray[tenticalIndex]->Bounds.Origin;
				float height = 105;
			
				TArray<FVector> PointsToCheck = {
					bottom + FVector(0, 0, height), 
					bottom + FVector(0, 0, height * 2)
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
					
					// if you see actor make it fade away
					if (!bHit || HitResult.GetActor() == Actor)
					{
						if (ATentacleWall* tentacle = Cast<ATentacleWall>(Actor))
						{
							if (isFocusing)
							{
								tentacle->FadeAway();
							}
						}
						break; 
					}
				}
			}
		}
		tenticalIndex++;
	}
	tenticalIndex = 0;
}

void UPlayerVision::LookForEye()
{
	PlayerLocation = PlayerCamera->GetComponentLocation();

	// check if the eye was recently rendered
	for (TObjectPtr<AActor> Actor : eyeArray)
	{
		if (IsValid(Actor) && Actor->WasRecentlyRendered(0.1f))
		{
			if (DotProduct(Actor->GetActorLocation()) > 0.54)
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
					
					// if you see actor make it fade away
					if (!bHit || HitResult.GetActor() == Actor)
					{
						// normal eyeball fading
						if (USpottedObject* eye = Cast<USpottedObject>(Actor->FindComponentByClass<USpottedObject>()))
						{
							eye->LookAtPlayer();
							if (isFocusing)
							{
								eye->FadeAway_Implementation();
							}
							else
							{
								eye->IncreaseMadness();
							}
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
	PlayerLocation = PlayerCamera->GetComponentLocation();
	
	// check if the eye was recently rendered
	for (TObjectPtr<AActor> Actor : bigEyeArray)
	{
		if (IsValid(Actor) && Actor->WasRecentlyRendered(0.1f))
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
	
				// if you see actor make it fade away
				if (!bHit || HitResult.GetActor() == Actor)
				{
					// big eyeball
					if (ABigEye* bigEye = Cast<ABigEye>(Actor))
					{
						// dot product
						// check if player is looking at big eye
						if (DotProduct(Actor->GetActorLocation()) > bigEye->radius)
						{
							FVector Dir = (Actor->GetActorLocation() - PlayerCamera->GetComponentLocation()).GetSafeNormal();
							
							FVector Forward = PlayerCamera->GetForwardVector();
							FVector Cross = FVector::CrossProduct(Forward, Dir);
							float Direction = FVector::DotProduct(Cross, PlayerCamera->GetUpVector());
							
							FVector Up = PlayerCamera->GetUpVector();
							float VerticalDot = FVector::DotProduct(Dir, Up);
							
							FRotator RelativeRotation = FRotator(FMath::Sign(VerticalDot) * -100, FMath::Sign(Direction) * -100, 0.0f);
							FRotator CurrentRotation = PlayerController->GetControlRotation();
							FRotator NewRotation = RelativeRotation + CurrentRotation;

							FRotator NewRotationt = FMath::RInterpTo(CurrentRotation, NewRotation, GetWorld()->GetDeltaSeconds(), bigEye->PushBackForce);
							PlayerController->SetControlRotation(NewRotationt);

							// make big eye look at player
							bigEye->LookAtPlayer();
							
							// if player is focusing fade the object 
							if (isFocusing)
							{
								bigEye->FadeAway();
							}
							bigEye->IncreaseMadness();
						}
					}
					break; 
				}
			}
		}
		bigEyeIndex++;
	}
	bigEyeIndex = 0;
}


void UPlayerVision::SetActorArray()
{
	tenticalArray.Empty();
	tenticalMeshArray.Empty();
	eyeArray.Empty();
	eyeMeshArray.Empty();
	bigEyeArray.Empty();
	bigEyeMeshArray.Empty();

	// add objects to array
	for (TActorIterator<ATentacleWall> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		TObjectPtr<ATentacleWall> Actor = *ActorItr;

		tenticalArray.Add(Actor);
		tenticalMeshArray.Add(Actor->FindComponentByClass<UMeshComponent>());
	}
	
	for (TActorIterator<ABigEye> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		TObjectPtr<ABigEye> Actor = *ActorItr;
		bigEyeArray.Add(Actor);
		bigEyeMeshArray.Add(Actor->FindComponentByClass<UMeshComponent>());
	}
	
	for (TActorIterator<AEye> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		TObjectPtr<AEye> Actor = *ActorItr;
		eyeArray.Add(Actor);
		eyeMeshArray.Add(Actor->FindComponentByClass<UMeshComponent>());
	}
}
