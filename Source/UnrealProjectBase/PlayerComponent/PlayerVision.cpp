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
	PlayerLocation = PlayerCamera->GetComponentLocation();
	LookForTentacleWall();
	LookForEye();
	LookForBigEye();
}

void UPlayerVision::LookForTentacleWall()
{
	if (!isFocusing) return;
	
	// check if the eye was recently rendered
	for (AActor* Actor : tenticalArray)
	{
		if (!IsValid(Actor) || Actor->IsPendingKillPending() || !Actor->IsValidLowLevel())
		{
			continue;
		}

		ATentacleWall* tentacle = Cast<ATentacleWall>(Actor);
		
		bool isTentacleWall = false;
		FVector bottom = tentacle->MovingSceneComponent->GetComponentLocation();
		TArray<FVector> PointsToCheck = {
			bottom,
			bottom + FVector(Actor->GetActorUpVector() * height), 
			bottom + FVector(Actor->GetActorUpVector() * height * 2)
		};
		
		for (FVector points : PointsToCheck)
		{
			if (DotProduct(points) > 0.54)
			{
				isTentacleWall = true;
			}
		}
		if (isTentacleWall == false)
		{
			continue;
		}
		
		if (tentacle->count >= 1)
		{
			tentacle->FadeAway();
			continue;
		}
		if (tentacle->isActive == false)
		{
			continue;
		}
		
		float Actordistance = FVector::Distance(PlayerCamera->GetComponentLocation(), tentacle->MovingSceneComponent->GetComponentLocation());
		if (Actordistance > distance)
		{
			continue;
		}
		
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
				tentacle->FadeAway();
				break; 
			}
		}
	}
}

void UPlayerVision::LookForEye()
{
	// check if the eye was recently rendered
	for (TObjectPtr<AActor> Actor : eyeArray)
	{
		if (!IsValid(Actor) || Actor->IsPendingKillPending() || !Actor->IsValidLowLevel())
		{
			EyeIndex++;
			continue;
		}
		if (!Actor->WasRecentlyRendered(0.1f))
		{
			EyeIndex++;
			continue;
		}
		if (DotProduct(Actor->GetActorLocation()) <= 0.54)
		{
			EyeIndex++;
			continue;
		}
		
		// check if the player has started making the object fade
		if (isFocusing)
		{
			if (USpottedObject* eye = Cast<USpottedObject>(Actor->FindComponentByClass<USpottedObject>()))
			{
				// fade object if the object is detected and don't need to raycast 
				if (eye->count >= 1)
				{
					eye->FadeAway_Implementation();
					EyeIndex++;
					continue;
				}
			}
		}
		
		float Actordistance = FVector::Distance(PlayerCamera->GetComponentLocation(), Actor->GetActorLocation());
		if (Actordistance > distance)
		{
			EyeIndex++;
			continue;	
		}

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
		EyeIndex++;
	}
	EyeIndex = 0;
}

void UPlayerVision::LookForBigEye()
{
	// check if the eye was recently rendered
	for (TObjectPtr<AActor> Actor : bigEyeArray)
	{
		if (!IsValid(Actor) || Actor->IsPendingKillPending() || !Actor->IsValidLowLevel())
		{
			bigEyeIndex++;
			continue;
		}
		if (!Actor->WasRecentlyRendered(0.1f))
		{
			bigEyeIndex++;
			continue;
		}
		float Actordistance = FVector::Distance(PlayerCamera->GetComponentLocation(), Actor->GetActorLocation());
		if (Actordistance > distance)
		{
			bigEyeIndex++;
			continue;
		}
		
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

						float vertical = FMath::Abs(VerticalDot);
						float horizontal = FMath::Abs(Direction);
						
						float pitch = VerticalDot/(vertical + horizontal);
						float yaw = Direction/(vertical + horizontal);
						
						FRotator RelativeRotation = FRotator(pitch * -100,yaw * -100, 0.0f);
						FRotator CurrentRotation = PlayerController->GetControlRotation();
						FRotator NewRotation = RelativeRotation + CurrentRotation;

						FRotator NewRotationt = FMath::RInterpTo(CurrentRotation, NewRotation, GetWorld()->GetDeltaSeconds(), bigEye->PushBackForce);
						PlayerController->SetControlRotation(NewRotationt);

						// make big eye look at player
						bigEye->LookAtPlayer();
						
						// if player is focusing fade the object 
						if (isFocusing)
						{
							bigEye->FadeAway_Implementation();
						}
						bigEye->IncreaseMadness();
					}
				}
				break; 
			}
		}
		bigEyeIndex++;
	}
	bigEyeIndex = 0;
}

void UPlayerVision::SetActorArray()
{
	tenticalArray.Empty();
	eyeArray.Empty();
	eyeMeshArray.Empty();
	bigEyeArray.Empty();
	bigEyeMeshArray.Empty();

	// add objects to array
	for (TActorIterator<ATentacleWall> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		TObjectPtr<ATentacleWall> Actor = *ActorItr;

		tenticalArray.Add(Actor);
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
