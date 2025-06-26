// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTeleport.h"

#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
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

	NextTeleportTo = CreateDefaultSubobject<USceneComponent>(TEXT("NextTeleportPoint"));
	NextTeleportTo->SetupAttachment(RootComponent);
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
	
	GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
	{
		TObjectPtr<APlayerController> PlayerController = GetWorld()->GetFirstPlayerController();
		TObjectPtr<APlayerHud> hud = Cast<APlayerHud>(PlayerController->GetHUD());

		widget = Cast<UMyUserWidget>(hud->GetMadnessMeterWidget());

		playerVision = PlayerController->GetPawn()->FindComponentByClass<UPlayerVision>();
	});
}


// loop player if puzzle is completed loop to next stage
// if next stage is null go to end screen
void AMyTeleport::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!Cast<ACharacter>(OtherActor)) return;
	if (!Cast<UCapsuleComponent>(OtherComp)) return;
	// check if this loop is null
	if (!teleportTo) return;
	
	// check if puzzle is completed
	if (isCompleted == true)
	{
		Player = OtherActor;
		LoadSubLevel_Implementation();
	}
	else
	{
		// teleport player
		Teleport(OtherActor, teleportTo->GetComponentTransform());
				
		// reset the eyes
		Reset();

		// increase their madness
		if (widget)
		{
			widget->IncreaseMadnessBar(increaseMadness);	
		}
	}
}

void AMyTeleport::LoadSubLevel_Implementation()
{
	LoadSubLevel();
	
	// loop until the loop is loaded to spawn the player
	GetWorld()->GetTimerManager().SetTimer(TimerHandleLevel, [this]()
	{
		if (NextLoopLevel.IsValid())
		{
			Teleport(Player, NextTeleportTo->GetComponentTransform());
			GetWorld()->GetTimerManager().ClearTimer(TimerHandleLevel);

			//unload current level
			unLoadSubLevel();
		}
	}, 0.1f, true);
}

void AMyTeleport::unLoadSubLevel_Implementation()
{
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

// respawn the selected objects
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

	// set the array for tentacle and eyes
	playerVision->SetActorArray();
}

void AMyTeleport::Teleport(AActor* OtherActor, FTransform Transform)
{
	FTransform destination = Transform;
	FTransform teleportStartPoint = this->GetTransform();
	FTransform player = OtherActor->GetTransform();
		
	FVector offset = player.GetLocation() - teleportStartPoint.GetLocation();
	FVector final = offset + destination.GetLocation();
		
	FTransform finalTeleport = FTransform(destination.GetRotation(), final, OtherActor->GetTransform().GetScale3D());
	
	OtherActor->SetActorTransform(finalTeleport, false, nullptr, ETeleportType::TeleportPhysics);
}