// All Rights Reserved by SweetSpot 2025-2026.


#include "Elevator.h"

#include "ElevatorPart.h"
#include "FMODBlueprintStatics.h"
#include "MyTeleport.h"
#include "UnrealProjectBase/UI/PlayerHud.h"
#include "UnrealProjectBase/PlayerComponent/PlayerInventory.h"
#include "GameFramework/Character.h"

// Sets default values
AElevator::AElevator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//set the childs
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

	//make the child invisible
	if (Switch && Switch->GetChildActor())
	{
		Switch->GetChildActor()->SetOwner(this);
		if (UStaticMeshComponent* Mesh = Switch->GetChildActor()->FindComponentByClass<UStaticMeshComponent>())
		{
			Mesh->SetVisibility(false);
			Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		}
	}
	if (Button && Button->GetChildActor())
	{
		Button->GetChildActor()->SetOwner(this);
		if (UStaticMeshComponent* Mesh = Button->GetChildActor()->FindComponentByClass<UStaticMeshComponent>())
		{
			Mesh->SetVisibility(false);
			Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		}
	}
	if (Cranck && Cranck->GetChildActor())
	{
		Cranck->GetChildActor()->SetOwner(this);
		if (UStaticMeshComponent* Mesh = Cranck->GetChildActor()->FindComponentByClass<UStaticMeshComponent>())
		{
			Mesh->SetVisibility(false);
			Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		}
	}
	
	SetChildPart(Switch, EElevatorPart::Switch);
	SetChildPart(Button, EElevatorPart::Button);
	SetChildPart(Cranck, EElevatorPart::Cranck);
}

void AElevator::SetChildPart(UChildActorComponent* Component, EElevatorPart Type)
{
	// give the child enum
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
	// if players inventory match the elevator part then fix elevator
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
						ShowElevatorPart(Switch);
					}
					break;

				case EElevatorPart::Button:
					if (Button)
					{
						ShowElevatorPart(Button);
					}
					break;

				case EElevatorPart::Cranck:
					if (Cranck)
					{
						ShowElevatorPart(Cranck);
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

void AElevator::ShowElevatorPart(UChildActorComponent* Part)
{
	// helper function make elevator parts appear 
	if (UStaticMeshComponent* Mesh = Part->GetChildActor()->FindComponentByClass<UStaticMeshComponent>())
	{
		Mesh->SetVisibility(true);
	}
	if (Teleport)
	{
		Teleport->isCompleted = true;
	}
	if (FixElevatorSFX)
	{
		UFMODBlueprintStatics::PlayEventAtLocation(this, FixElevatorSFX, this->GetActorTransform(), true);	
	}
}


