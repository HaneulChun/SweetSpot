// All Rights Reserved by SweetSpot 2025-2026.


#include "TentacleWall.h"

#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "UnrealProjectBase/UI/MyUserWidget.h"
#include "UnrealProjectBase/UI/PlayerHud.h"

// Sets default values
ATentacleWall::ATentacleWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	// set trigger-box for default
	triggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	triggerBox->SetupAttachment(RootComponent);
	triggerBox->SetCollisionProfileName(TEXT("Trigger"));
	triggerBox->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void ATentacleWall::BeginPlay()
{
	Super::BeginPlay();

	triggerBox->OnComponentBeginOverlap.AddDynamic(this, &ATentacleWall::OnOverlapBegin);
	triggerBox->OnComponentEndOverlap.AddDynamic(this, &ATentacleWall::OnOverlapEnd);

	GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		APlayerHud* hud = Cast<APlayerHud>(PlayerController->GetHUD());

		widget = Cast<UMyUserWidget>(hud->GetMadnessMeterWidget());
	});

	startTransform = GetTransform();
	startLocation = GetActorLocation().Z;
	finalLocation = GetActorLocation().Z - 400;
}

void ATentacleWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// tentacle fading up
	if (isSpawning)
	{
		// move the object
		FVector CurrentLocation = GetActorLocation();
		SetActorLocation(CurrentLocation + (GetActorUpVector() * 1));
		
		if (CurrentLocation.Z >= startLocation)
		{
			isSpawning = false;
		}
	}
}

void ATentacleWall::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!Cast<ACharacter>(OtherActor)) return;
	if (!Cast<UCapsuleComponent>(OtherComp)) return;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATentacleWall::IncreaseMadnessBar, 0.4, true);
}

void ATentacleWall::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!Cast<ACharacter>(OtherActor)) return;
	if (!Cast<UCapsuleComponent>(OtherComp)) return;

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}


void ATentacleWall::IncreaseMadnessBar()
{
	if (!widget) return;
	widget->IncreaseMadnessBar(IncreaseMadness);
}


void ATentacleWall::FadeAway()
{
	// move the object
	if (count <= focusedLookTicks)
	{
		// make eye disappear 
		FVector Direction = -GetActorUpVector();
		FVector CurrentLocation = GetActorLocation();
		FVector NewLocation = CurrentLocation + (Direction * speed);
		SetActorLocation(NewLocation);

		CameraShake();
		
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ATentacleWall::ResetTentaclePosition_Implementation, 1.0f, false, 0.4f);
	}
	else
	{
		widget->IncreaseMadnessBar(-restoreMadnessValue);
		// destroy actor
		DestroyTentacle();
	}
	count++;
}

void ATentacleWall::Spawn()
{
	isSpawning = true;
}

void ATentacleWall::StartDown()
{
	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, finalLocation));
}

void ATentacleWall::ResetTentaclePosition_Implementation()
{
	ResetTentaclePosition();
	SetActorTransform(startTransform);
	count = 0;
}

