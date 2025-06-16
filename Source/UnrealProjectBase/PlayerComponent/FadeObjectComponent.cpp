// All Rights Reserved by SweetSpot 2025-2026.


#include "FadeObjectComponent.h"

#include "UnrealProjectBase/UI/MyUserWidget.h"
#include "UnrealProjectBase/UI/PlayerHud.h"
#include "EngineUtils.h"

// Sets default values for this component's properties
UFadeObjectComponent::UFadeObjectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFadeObjectComponent::BeginPlay()
{
	Super::BeginPlay();


	GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		APlayerHud* hud = Cast<APlayerHud>(PlayerController->GetHUD());

		widget = Cast<UMyUserWidget>(hud->GetMadnessMeterWidget());

		StartLoop();
	});
}


void UFadeObjectComponent::StartLoop()
{
	widget->CurrentState = ECurrentState::Dead;
	SaneActors.Empty();
	SweetActors.Empty();
	spawnPoint = nullptr;
	
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		TObjectPtr<AActor> Actor = *ActorItr;
		
		if (Actor->Tags.Contains("Sane"))
		{
			SaneActors.Add(Actor);
		}
		else if (Actor->Tags.Contains("Sweet"))
		{
			SweetActors.Add(Actor);
		}
		else if (Actor->Tags.Contains("Spawn"))
		{
			spawnPoint = Actor;
		}
	}
}