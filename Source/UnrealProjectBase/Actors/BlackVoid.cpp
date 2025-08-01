// All Rights Reserved by SweetSpot 2025-2026.


#include "BlackVoid.h"

#include "SweetSpotCharacter.h"
#include "VectorTypes.h"
#include "Components/BillboardComponent.h"
#include "Components/BoxComponent.h"
#include "UnrealProjectBase/Component/CameraSettingsComponent.h"
#include "UnrealProjectBase/UI/PlayerHud.h"

// Sets default values
ABlackVoid::ABlackVoid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	moveingComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Moveing"));
	moveingComponent->SetupAttachment(RootComponent);
	
	start = CreateDefaultSubobject<USceneComponent>(TEXT("Start"));
	start->SetupAttachment(RootComponent);
	CreateDefaultSubobject<UBillboardComponent>(TEXT("StartBillboard"))->SetupAttachment(start);

	end = CreateDefaultSubobject<USceneComponent>(TEXT("End"));
	end->SetupAttachment(RootComponent);
	CreateDefaultSubobject<UBillboardComponent>(TEXT("EndBillboard"))->SetupAttachment(end);

	blackVoid = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlackVoid"));
	blackVoid->SetupAttachment(moveingComponent);

	triggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	triggerBox->SetupAttachment(blackVoid);
	triggerBox->SetCollisionProfileName(TEXT("Trigger"));
	triggerBox->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void ABlackVoid::BeginPlay()
{
	Super::BeginPlay();

	moveingComponent->SetWorldLocation(start->GetComponentLocation());
	blackVoid->AttachToComponent(moveingComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	triggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	blackVoid->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	blackVoid->SetHiddenInGame(true);

	PrimaryActorTick.SetTickFunctionEnable(true);
	SetActorTickEnabled(false);

	player = Cast<ASweetSpotCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	CameraSettings = GetWorld()->GetFirstPlayerController()->GetPawn()->FindComponentByClass<UCameraSettingsComponent>();
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
		moveingComponent->SetWorldLocation(NewLocation);
		//float distance = GetDistanceTo(player);
		float distance = UE::Geometry::Distance(moveingComponent->GetComponentLocation(), player->GetActorLocation());

		// very clsoe
		if (distance < 500 && DistanceState != EDistance::veryClose)
		{
			CameraSettings->SetCameraSettings(1, 3, 90);
			DistanceState = EDistance::close;
		}
		// close
		else if (distance < 1000 && DistanceState != EDistance::close)
		{
			CameraSettings->SetCameraSettings(1, 2, 90);
			DistanceState = EDistance::close;
		}
		else if (distance < 1500 && DistanceState != EDistance::far)
		{
			CameraSettings->SetCameraSettings(1, 1, 90);
			DistanceState = EDistance::far;
		}
	}
	else
	{
		SetActorTickEnabled(false);
	}
}

void ABlackVoid::StartVoid()
{
	SetActorTickEnabled(true);

	triggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	blackVoid->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	blackVoid->SetHiddenInGame(false);
	PlaySound();
}

