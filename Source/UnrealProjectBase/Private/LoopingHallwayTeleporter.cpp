// Fill out your copyright notice in the Description page of Project Settings.


#include "LoopingHallwayTeleporter.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ALoopingHallwayTeleporter::ALoopingHallwayTeleporter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	triggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	triggerBox->SetupAttachment(RootComponent);
	triggerBox->SetCollisionProfileName(TEXT("Trigger"));
	triggerBox->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void ALoopingHallwayTeleporter::BeginPlay()
{
	Super::BeginPlay();

	for (AActor* objects : Actors)
	{
		if (objects)
		{
			location.Add(objects->GetActorLocation());
		}
	}
	
	triggerBox->OnComponentBeginOverlap.AddDynamic(this, &ALoopingHallwayTeleporter::OnOverlapBegin);
}

// loop player if puzzle is completed loop to next stage
// if next stage is null go to end screen
void ALoopingHallwayTeleporter::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ACharacter* Character = Cast<ACharacter>(OtherActor))
	{
		if (isCompleted == true)
		{
			Complete(OtherActor);
		}
		else
		{
			Teleport(OtherActor, thisLoop);
			
			Reset();

			APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
			if (APlayerController* character = Cast<APlayerController>(PlayerController))
			{
				// TODO increase the increase the madnessbar
			}

			if (UCapsuleComponent* Capsule = Character->GetCapsuleComponent())
			{
				Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        
				// Re-enable after delay
				FTimerHandle TimerHandle;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, [Capsule]()
				{
					if (Capsule)
					{
						Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
					}
				}, 0.3f, false);
			}
		}
	}
}

void ALoopingHallwayTeleporter::Reset()
{
	Super::Reset();

	int32 i = 0;
	for (AActor* object : Actors)
	{
		if (object)
		{
			object->Destroy();
		
			FRotator SpawnRotation = FRotator::ZeroRotator;
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			
			GetWorld()->SpawnActor<AActor>(object->GetClass(), location[i], SpawnRotation, SpawnParams);
			i++;
		}
	}
}

void ALoopingHallwayTeleporter::Complete(AActor* OtherActor)
{
	OtherActor->SetActorLocation(nextLoop);
}

void ALoopingHallwayTeleporter::Teleport(AActor* OtherActor, FVector Transform)
{
	FVector offset = OtherActor->GetActorLocation() - this->GetActorLocation();
	FVector finalLocation = offset + GetActorTransform().TransformPosition(Transform);
	
	FTransform finalTransform(FRotator::ZeroRotator, finalLocation, OtherActor->GetActorScale3D());
	OtherActor->SetActorTransform(finalTransform, false);
}

