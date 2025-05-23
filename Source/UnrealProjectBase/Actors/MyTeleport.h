// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"

#include "MyTeleport.generated.h"

class ACharacter;
class UBoxComponent;
UCLASS()
class UNREALPROJECTBASE_API AMyTeleport : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyTeleport();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY()
	TArray<FVector> location;

	UPROPERTY()
	TArray<FRotator> rotation;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSoftObjectPtr<UWorld>> levelLoop;
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* thisLoop;

	UPROPERTY(BlueprintReadOnly)
	float currentLoop = 0;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void SetActors();
	
	UFUNCTION()
	void Reset();

	UFUNCTION(BlueprintCallable)
	void Complete();

	UFUNCTION()
	void Teleport(AActor* OtherActor);
	
	UPROPERTY(BlueprintReadWrite)
	bool isCompleted = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<AActor>> Actors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float increaseMadness = 0.1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trigger")
	UBoxComponent* triggerBox;
};
