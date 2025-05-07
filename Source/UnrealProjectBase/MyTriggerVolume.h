// MyTriggerVolume.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"
#include "MyTriggerVolume.generated.h"

UCLASS()
class UNREALPROJECTBASE_API AMyTriggerVolume : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyTriggerVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:    
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Trigger Volume component to detect overlap
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerVolume;

	// Niagara effect to spawn (set to "NS_Smoke" or any other effect)
	UPROPERTY(EditAnywhere, Category = "Effects")
	UNiagaraSystem* NiagaraEffect;

	// Niagara component to spawn
	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* NiagaraComponent;

	// Event handlers for overlap
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
						UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, 
						const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
					  UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);
};
