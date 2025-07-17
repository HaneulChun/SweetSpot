// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"

#include "MyTeleport.generated.h"

class UCameraSettingsComponent;
class UCameraComponent;
class UArrowComponent;
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
	UPROPERTY()
	TObjectPtr<UPlayerVision> playerVision;

	bool hasTeleported = false;
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
	
	UPROPERTY()
	TObjectPtr<UCameraSettingsComponent> CameraSettings;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UWorld> NextLoopLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UWorld> thisLoopLevel;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> teleportTo;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UArrowComponent> Arrow;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> NextTeleportTo;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UArrowComponent> nextArrow;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void LoadSubLevel();
	
	UFUNCTION()
	void SetActors();
	
	UFUNCTION()
	void Reset();

	UFUNCTION(BlueprintCallable)
	void Teleport(AActor* OtherActor, UArrowComponent* ArrowComponent);
	
	UPROPERTY(BlueprintReadWrite)
	bool isCompleted = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TeleportLoop")
	TArray<TObjectPtr<AActor>> Actors;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trigger")
	TObjectPtr<UBoxComponent> triggerBox;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TeleportLoop")
	float increaseMadness = 0.1;
};
