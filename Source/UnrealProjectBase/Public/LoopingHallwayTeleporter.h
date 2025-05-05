// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LoopingHallwayTeleporter.generated.h"

class UBoxComponent;
UCLASS()
class UNREALPROJECTBASE_API ALoopingHallwayTeleporter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALoopingHallwayTeleporter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
    TArray<FVector> location;
public:	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MakeEditWidget), Category = "Teleport")
	FVector thisLoop;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MakeEditWidget), Category = "Teleport")
	FVector nextLoop;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void Reset();

	UFUNCTION()
	void Complete(AActor* OtherActor);

	UFUNCTION()
	void Teleport(AActor* OtherActor, FTransform Transform);
	
	UPROPERTY()
	bool isCompleted = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleport")
	TArray<TObjectPtr<AActor>> Actors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleport")
	float increaseMadness = 0.1;
	
	UPROPERTY()
	UBoxComponent* triggerBox;
};
