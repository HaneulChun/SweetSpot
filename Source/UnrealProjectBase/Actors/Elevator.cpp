// All Rights Reserved by SweetSpot 2025-2026.


#include "Elevator.h"

#include "ElevatorPart.h"
#include "FMODBlueprintStatics.h"
#include "MyTeleport.h"
#include "UnrealProjectBase/PlayerComponent/PlayerInventory.h"

// Sets default values
AElevator::AElevator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	//set the children
	Switch = CreateDefaultSubobject<UChildActorComponent>(TEXT("Switch"));
	Switch->SetupAttachment(RootComponent);
	
	Button = CreateDefaultSubobject<UChildActorComponent>(TEXT("Button"));
	Button->SetupAttachment(RootComponent);
	
	Cranck = CreateDefaultSubobject<UChildActorComponent>(TEXT("Crank"));
	Cranck->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AElevator::BeginPlay()
{
	Super::BeginPlay();

	//make the child invisible
	if (Switch && Switch->GetChildActor())
	{
		if (TurnOnSwitch == false)
		{
			Switch->GetChildActor()->SetOwner(this);
			Switch->SetVisibility(false);
		}
	}
	if (Button && Button->GetChildActor())
	{
		if (TurnOnButton == false)
		{
			Button->GetChildActor()->SetOwner(this);
			Button->SetVisibility(false);
		}
	}
	if (Cranck && Cranck->GetChildActor())
	{
		if (TurnOnCranck == false)
		{
			Cranck->GetChildActor()->SetOwner(this);
			Cranck->SetVisibility(false);
		}
	}
	
	SetChildPart(Switch, EElevatorPart::Switch);
	SetChildPart(Button, EElevatorPart::Button);
	SetChildPart(Cranck, EElevatorPart::Cranck);
}

void AElevator::SetChildPart(UChildActorComponent* Component, EElevatorPart Type)
{
	 //give the child enum
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
				
				Inventory->GetElevatorPart(EElevatorPart::None);
			}
		}
	}
}

void AElevator::ShowElevatorPart(UChildActorComponent* Part)
{
	// helper function make elevator parts appear 
	Part->SetVisibility(true);
	if (Teleport)
	{
		Teleport->isCompleted = true;
	}
	if (FixElevatorSFX)
	{
		UFMODBlueprintStatics::PlayEventAtLocation(this, FixElevatorSFX, this->GetActorTransform(), true);	
	}
	Exit();
}

void AElevator::Exit_Implementation()
{
}

void AElevator::Highlight(EElevatorPart Part)
{
}