// All Rights Reserved by SweetSpot 2025-2026.


#include "teleport.h"

#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"

// Sets default values
Ateleport::Ateleport()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
	// set trigger-box for default
	triggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	triggerBox->SetupAttachment(RootComponent);
	triggerBox->SetCollisionProfileName(TEXT("Trigger"));
	triggerBox->SetGenerateOverlapEvents(true);


	// Create the Arrow Component
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPoint"));
	ArrowComponent->SetupAttachment(RootComponent); 
	ArrowComponent->ArrowColor = FColor::Green;
}

void Ateleport::BeginPlay()
{
	Super::BeginPlay();

	triggerBox->OnComponentBeginOverlap.AddDynamic(this, &Ateleport::OnOverlapBegin);
}

void Ateleport::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// check if other actor is player and check if they are close enough 
	if (Cast<ACharacter>(OtherActor))
	{
		if (Cast<UCapsuleComponent>(OtherComp))
		{
			if (teleportTo)
			{
				Teleport(OtherActor);
			}
			ShowElevatorPart();
		}
	}
}

void Ateleport::Teleport(AActor* OtherActor)
{
	if (ACharacter* Character = Cast<ACharacter>(OtherActor))
	{
		FVector location = teleportTo->ArrowComponent->GetComponentLocation();
		FRotator rotation = teleportTo->ArrowComponent->GetComponentRotation();

		// Ensure the controller gets rotated too, or it will snap back
		Character->Controller->SetControlRotation(rotation);

		// Teleport character using proper function
		Character->TeleportTo(location, rotation);
	}
	else
	{
		// Fallback for non-character actors
		FVector location = teleportTo->ArrowComponent->GetComponentLocation();
		FRotator rotation = teleportTo->ArrowComponent->GetComponentRotation();
		OtherActor->SetActorLocationAndRotation(location, rotation, false, nullptr, ETeleportType::TeleportPhysics);
	}
}



