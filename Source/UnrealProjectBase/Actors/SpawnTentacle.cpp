// All Rights Reserved by SweetSpot 2025-2026.

#include "SpawnTentacle.h"

#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ASpawnTentacle::ASpawnTentacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	// set trigger-box for default
	triggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	triggerBox->SetupAttachment(RootComponent);
	triggerBox->SetCollisionProfileName(TEXT("Trigger"));
	triggerBox->SetGenerateOverlapEvents(true);

	spawnTentacle = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	spawnTentacle->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASpawnTentacle::BeginPlay()
{
	Super::BeginPlay();
	
}
