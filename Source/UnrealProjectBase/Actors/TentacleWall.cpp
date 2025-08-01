// All Rights Reserved by SweetSpot 2025-2026.


#include "TentacleWall.h"

#include "SweetSpotCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UnrealProjectBase/UI/MyUserWidget.h"
#include "UnrealProjectBase/UI/PlayerHud.h"

// Sets default values
ATentacleWall::ATentacleWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	MovingSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("MovingComponent"));
	MovingSceneComponent->SetupAttachment(RootComponent);
	
	// set trigger-box for default
	triggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	triggerBox->SetupAttachment(MovingSceneComponent);
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

		Character = Cast<ASweetSpotCharacter>(PlayerController->GetPawn());
		OriginalSpeed = Character->GetCharacterMovement()->MaxWalkSpeed;
	});

	SetActorTickEnabled(false);
	
	startLocation = GetActorLocation() + GetActorUpVector();
	finalLocation = GetActorLocation() + (-GetActorUpVector() * 400);
}

void ATentacleWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// tentacle fading up
	currentAlpha += comingUpSpeed * DeltaTime;
	FVector NewLocation = FMath::Lerp(finalLocation, startLocation, currentAlpha);
	MovingSceneComponent->SetWorldLocation(NewLocation);
		
	if (currentAlpha >= 1)
	{
		SetActorTickEnabled(false);
	}
}

void ATentacleWall::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ACharacter* OverlappingCharacter = Cast<ACharacter>(OtherActor))
	{
		if (!Cast<UCapsuleComponent>(OtherComp)) return;

		// give damage too player
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATentacleWall::IncreaseMadnessBar, 0.4, true);

		// reset speed
		if (OverlappingCharacter->GetCharacterMovement())
		{
			// slow down player
			OverlappingCharacter->GetCharacterMovement()->MaxWalkSpeed = slowPlayer;
		}
	}
}

void ATentacleWall::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ACharacter* OverlappingCharacter = Cast<ACharacter>(OtherActor))
	{
		if (!Cast<UCapsuleComponent>(OtherComp)) return;

		// end damage timer
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

		// reset speed
		if (OverlappingCharacter->GetCharacterMovement())
		{
			OverlappingCharacter->GetCharacterMovement()->MaxWalkSpeed = OriginalSpeed;
		}
	}
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
		FVector CurrentLocation = MovingSceneComponent->GetComponentLocation();
		FVector NewLocation = CurrentLocation + (Direction * speed);
		MovingSceneComponent->SetWorldLocation(NewLocation);

		CameraShake();
		
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ATentacleWall::ResetTentaclePosition_Implementation, 1.0f, false, 0.4f);
	}
	else
	{
		widget->DecreaseMadness(restoreMadnessValue);
		// destroy actor
		DestroyTentacle();
	}
	count++;
}

void ATentacleWall::Spawn()
{
	SetActorTickEnabled(true);
}

void ATentacleWall::StartDown()
{
	MovingSceneComponent->SetWorldLocation(finalLocation);
}

void ATentacleWall::ResetTentaclePosition_Implementation()
{
	ResetTentaclePosition();
	finalLocation = MovingSceneComponent->GetComponentLocation();
	currentAlpha = 0;
	SetActorTickEnabled(true);
	count = 0;
}

