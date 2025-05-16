// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTeleport.h"

#include "EngineUtils.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "PlayerHud.h"
#include "MyUserWidget.h"
#include "PlayerVision.h"

// Sets default values
AMyTeleport::AMyTeleport()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	triggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	triggerBox->SetupAttachment(RootComponent);
	triggerBox->SetCollisionProfileName(TEXT("Trigger"));
	triggerBox->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void AMyTeleport::BeginPlay()
{
	Super::BeginPlay();

	for (AActor* objects : Actors)
	{
		if (objects)
		{
			location.Add(objects->GetActorLocation());
		}
	}

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
		if (thisLoop)
		{
			if (isCompleted == true)
			{
				Complete(OtherActor);
			}
			else
			{
				Teleport(OtherActor, thisLoop->GetTransform());
				
				Reset();

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

void AMyTeleport::Reset()
{
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

void AMyTeleport::Complete(AActor* OtherActor)
{
	if (nextLoop)
	{
		Teleport(OtherActor, nextLoop->GetTransform());
		return;
	}
	UObject* t = Cast<UObject>(OtherActor);
	UGameplayStatics::OpenLevel(t, "WinScrean");
}

void AMyTeleport::Teleport(AActor* OtherActor, FTransform Transform)
{
	FTransform destanation = Transform;
	FTransform teleportStartPoint = this->GetTransform();
	FTransform player = OtherActor->GetTransform();
		
	FVector offset = player.GetLocation() - teleportStartPoint.GetLocation();
	FVector final = offset + destanation.GetLocation();
		
	FTransform finalTeleport = FTransform(destanation.GetRotation(), final, OtherActor->GetTransform().GetScale3D());
	OtherActor->SetActorTransform(finalTeleport, false);
}

