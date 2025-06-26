// All Rights Reserved by SweetSpot 2025-2026.


#include "BlackVoid.h"

#include "Components/ArrowComponent.h"
#include "Components/BillboardComponent.h"

// Sets default values
ABlackVoid::ABlackVoid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	start = CreateDefaultSubobject<USceneComponent>(TEXT("Start"));
	start->SetupAttachment(RootComponent);
	CreateDefaultSubobject<UBillboardComponent>(TEXT("StartBillboard"))->SetupAttachment(start);

	end = CreateDefaultSubobject<USceneComponent>(TEXT("End"));
	end->SetupAttachment(RootComponent);
	CreateDefaultSubobject<UBillboardComponent>(TEXT("EndBillboard"))->SetupAttachment(end);

	blackVoid = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlackVoid"));
	blackVoid->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABlackVoid::BeginPlay()
{
	Super::BeginPlay();

	blackVoid->SetWorldLocation(start->GetComponentLocation());
	
	blackVoid->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//blackVoid->SetHiddenInGame(true);
}

// Called every frame
void ABlackVoid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ElapsedTime < MoveDuration)
	{
		ElapsedTime += DeltaTime;
		float Alpha = FMath::Clamp(ElapsedTime / MoveDuration, 0.0f, 1.0f);
		FVector NewLocation = FMath::Lerp(start->GetComponentLocation(), end->GetComponentLocation(), Alpha);
		blackVoid->SetWorldLocation(NewLocation);
	}
}

