// All Rights Reserved by SweetSpot 2025-2026.


#include "teleport.h"
#include "Components/BoxComponent.h"
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
}

void Ateleport::BeginPlay()
{
	Super::BeginPlay();

	triggerBox->OnComponentBeginOverlap.AddDynamic(this, &Ateleport::OnOverlapBegin);
}

void Ateleport::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ACharacter>(OtherActor))
	{
		if (teleportTo)
		{
			Teleport(OtherActor);
		}
	}
}

void Ateleport::Teleport(AActor* OtherActor)
{
	FTransform destanation = teleportTo->GetTransform();
	FTransform teleportStartPoint = this->GetTransform();
	FTransform player = OtherActor->GetTransform();
		
	FVector offset = player.GetLocation() - teleportStartPoint.GetLocation();
	FVector final = offset + destanation.GetLocation();
		
	FTransform finalTeleport = FTransform(destanation.GetRotation(), final, OtherActor->GetTransform().GetScale3D());
	OtherActor->SetActorTransform(finalTeleport, false);
}



