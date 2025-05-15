// All Rights Reserved by SweetSpot 2025-2026.


#include "Elevator.h"

#include "ElevatorPart.h"
#include "MyTeleport.h"
#include "PlayerInventory.h"
#include "GameFramework/Character.h"

// Sets default values
AElevator::AElevator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Switch = CreateDefaultSubobject<UChildActorComponent>(TEXT("Switch"));
	Switch->SetupAttachment(RootComponent);
	
	Button = CreateDefaultSubobject<UChildActorComponent>(TEXT("Button"));
	Button->SetupAttachment(RootComponent);
	
	Cranck = CreateDefaultSubobject<UChildActorComponent>(TEXT("Cranck"));
	Cranck->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AElevator::BeginPlay()
{
	Super::BeginPlay();
	
	if (Switch && Switch->GetChildActor())
	{
		Switch->GetChildActor()->SetOwner(this);
		if (UStaticMeshComponent* Mesh = Switch->GetChildActor()->FindComponentByClass<UStaticMeshComponent>())
		{
			Mesh->SetVisibility(false);
			Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
	if (Button && Button->GetChildActor())
	{
		Button->GetChildActor()->SetOwner(this);
		if (UStaticMeshComponent* Mesh = Button->GetChildActor()->FindComponentByClass<UStaticMeshComponent>())
		{
			Mesh->SetVisibility(false);
			Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
	if (Cranck && Cranck->GetChildActor())
	{
		Cranck->GetChildActor()->SetOwner(this);
		if (UStaticMeshComponent* Mesh = Cranck->GetChildActor()->FindComponentByClass<UStaticMeshComponent>())
		{
			Mesh->SetVisibility(false);
			Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}

	InitPart(Switch, EElevatorPart::Switch);
	InitPart(Button, EElevatorPart::Button);
	InitPart(Cranck, EElevatorPart::Cranck);
}

void AElevator::InitPart(UChildActorComponent* Component, EElevatorPart Type)
{
	if (Component && Component->GetChildActor())
	{
		if (AElevatorPart* Part = Cast<AElevatorPart>(Component->GetChildActor()))
		{
			Part->ElevatorPart = Type;
		}
	}
}

void AElevator::FixElevator()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (APawn* Pawn = PlayerController->GetPawn())
		{
			if (UPlayerInventory* Inventory = Pawn->FindComponentByClass<UPlayerInventory>())
			{
				ElevatorPart = Inventory->ElevatorPart;

				switch (ElevatorPart)
				{
				case EElevatorPart::Switch:
					if (Switch)
					{
						if (UStaticMeshComponent* Mesh = Switch->GetChildActor()->FindComponentByClass<UStaticMeshComponent>())
						{
							Mesh->SetVisibility(true);
							if (Teleport)
							{
								Teleport->isCompleted = true;
							}
						}
					}
					break;

				case EElevatorPart::Button:
					if (Button)
					{
						if (UStaticMeshComponent* Mesh = Button->GetChildActor()->FindComponentByClass<UStaticMeshComponent>())
						{
							Mesh->SetVisibility(true);
							if (Teleport)
							{
								Teleport->isCompleted = true;
							}
						}
					}
					break;

				case EElevatorPart::Cranck:
					if (Cranck)
					{
						if (UStaticMeshComponent* Mesh = Cranck->GetChildActor()->FindComponentByClass<UStaticMeshComponent>())
						{
							Mesh->SetVisibility(true);
							if (Teleport)
							{
								Teleport->isCompleted = true;
							}
						}
					}
					break;

				default:
					break;
				}

				Inventory->ElevatorPart =  EElevatorPart::None;
			}
		}
	}
}


