// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"

#include "MyTeleport.generated.h"

class UPlayerVision;
class UMyUserWidget;
class ACharacter;
class UBoxComponent;
class UMyUSerWidgetComponent;
UCLASS()
class UNREALPROJECTBASE_API AMyTeleport : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyTeleport();

private:
	TObjectPtr<UPlayerVision> playerVision;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY()
	TArray<FVector> location;
	UPROPERTY()
	TArray<FRotator> rotation;

	UPROPERTY()
	TObjectPtr<UMyUserWidget> widget;

	UPROPERTY()
	TObjectPtr<AActor> Player;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TeleportLoop")
	TSoftObjectPtr<UWorld> NextLoopLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TeleportLoop")
	TSoftObjectPtr<UWorld> thisLoopLevel;
	
	UPROPERTY(VisibleAnywhere, Category = "TeleportLoop")
	TObjectPtr<USceneComponent> teleportTo;

	UPROPERTY(VisibleAnywhere, Category = "TeleportLoop")
	TObjectPtr<USceneComponent> NextTeleportTo;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void LoadSubLevel();
	virtual void LoadSubLevel_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void unLoadSubLevel();
	virtual void unLoadSubLevel_Implementation();

	FTimerHandle TimerHandleLevel;
	
	UFUNCTION()
	void SetActors();
	
	UFUNCTION()
	void Reset();

	UFUNCTION()
	void Teleport(AActor* OtherActor, FTransform Transform);
	
	UPROPERTY(BlueprintReadWrite)
	bool isCompleted = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TeleportLoop")
	TArray<TObjectPtr<AActor>> Actors;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trigger")
	TObjectPtr<UBoxComponent> triggerBox;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TeleportLoop")
	float increaseMadness = 0.1;
};
