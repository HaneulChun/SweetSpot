// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTeleport.h"

#include "Components/BoxComponent.h"
#include "Engine/Engine.h"
#include "GameFramework/Character.h"
#include "UnrealProjectBase/UI/PlayerHud.h"
#include "UnrealProjectBase/UI/MyUserWidget.h"
#include "UnrealProjectBase/PlayerComponent/PlayerVision.h"

// Sets default values
AMyTeleport::AMyTeleport()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
	// set trigger-box for default
	triggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	triggerBox->SetupAttachment(RootComponent);
	triggerBox->SetCollisionProfileName(TEXT("Trigger"));
	triggerBox->SetGenerateOverlapEvents(true);

	teleportTo = CreateDefaultSubobject<USceneComponent>(TEXT("TeleportPoint"));
	teleportTo->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMyTeleport::BeginPlay()
{
	Super::BeginPlay();

	SetActors();
	
	if (triggerBox)
	{
		triggerBox->OnComponentBeginOverlap.AddDynamic(this, &AMyTeleport::OnOverlapBegin);
	}
}

// loop player if puzzle is completed loop to next stage
// if next stage is null go to end screen
void AMyTeleport::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ACharacter>(OtherActor))
	{
		// check if this loop is null
		if (teleportTo)
		{
			// teleport player
			Teleport(OtherActor);
			
			// check if puzzle is completed
			if (isCompleted == true)
			{
				Complete();
			}
			else
			{
				// reset the eye and chocolate 
				Reset();

				// increase their madness
				APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
				if (APlayerController* character = Cast<APlayerController>(PlayerController))
				{
					APlayerHud* hud = Cast<APlayerHud>(character->GetHUD());

					UMyUserWidget* widget = Cast<UMyUserWidget>(hud->GetWidget());
					if (widget)
					{
						widget->IncreaseMadnessBar(increaseMadness);
					}	
				}
			}
		}	
	}
}

void AMyTeleport::SetActors()
{
	for (AActor* objects : Actors)
	{
		if (objects)
		{
			location.Add(objects->GetActorLocation());
			rotation.Add(objects->GetActorRotation());
		}
	}
}

void AMyTeleport::Reset()
{
	int32 i = 0;
	for (AActor* object : Actors)
	{
		if (object)
		{
			object->Destroy();
			
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;


			GetWorld()->SpawnActor<AActor>(object->GetClass(), location[i], rotation[i], SpawnParams);
			i++;
		}
	}
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		APawn* PlayerPawn = PC->GetPawn();
		if (PlayerPawn)
		{
			UPlayerVision* VisionComp = PlayerPawn->FindComponentByClass<UPlayerVision>();
			if (VisionComp)
			{
				VisionComp->SetActorArray();
			}
		}
	}
}

void AMyTeleport::Complete()
{
	currentLoop++;
	
	if (levelLoop.Num() > currentLoop)
	{
		isCompleted = false;
	}
}

void AMyTeleport::Teleport(AActor* OtherActor)
{
	FTransform destanation = teleportTo->GetComponentTransform();
	FTransform teleportStartPoint = this->GetTransform();
	FTransform player = OtherActor->GetTransform();
		
	FVector offset = player.GetLocation() - teleportStartPoint.GetLocation();
	FVector final = offset + destanation.GetLocation();
		
	FTransform finalTeleport = FTransform(destanation.GetRotation(), final, OtherActor->GetTransform().GetScale3D());
	OtherActor->SetActorTransform(finalTeleport, false);
}

