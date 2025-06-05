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

	Tags.Add("Tentical");
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

		widget = Cast<UMyUserWidget>(hud->GetWidget());
	});
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

// Called every frame
void ATentacleWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

