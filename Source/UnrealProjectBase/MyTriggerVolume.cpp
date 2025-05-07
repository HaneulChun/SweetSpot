// MyTriggerVolume.cpp

#include "MyTriggerVolume.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
AMyTriggerVolume::AMyTriggerVolume()
{
    // Set this actor to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;

    // Create the Trigger Volume as a Box Component
    TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
    RootComponent = TriggerVolume; // Set the RootComponent of the actor to be the trigger volume

    // Bind the overlap events
    TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AMyTriggerVolume::OnOverlapBegin);
    TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &AMyTriggerVolume::OnOverlapEnd);

    // Set default NiagaraEffect to "NS_Smoke" (adjust this path if needed)
    static ConstructorHelpers::FObjectFinder<UNiagaraSystem> DefaultNiagaraEffect(TEXT("NiagaraSystem'/All/Content/Jason/VFX/NS_Smoke'"));
    if (DefaultNiagaraEffect.Succeeded())
    {
        NiagaraEffect = DefaultNiagaraEffect.Object;
    }
}

// Called when the game starts or when spawned
void AMyTriggerVolume::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AMyTriggerVolume::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMyTriggerVolume::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                       UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, 
                                       const FHitResult& SweepResult)
{
    if (NiagaraEffect)
    {
        // Spawn the Niagara effect at the trigger's location
        if (!NiagaraComponent)
        {
            // NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(OtherActor, NiagaraEffect, GetActorLocation());
        }
    }
}

void AMyTriggerVolume::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
    // Here you can stop the Niagara effect or do any reset if needed
    if (NiagaraComponent)
    {
        NiagaraComponent->Deactivate();
    }
}
