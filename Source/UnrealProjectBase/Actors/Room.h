// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"

#include "Room.generated.h"

class UCameraSettingsComponent;
class UCameraComponent;
class ACharacter;
class UBoxComponent;
class UMyUserWidget;
UCLASS()
class UNREALPROJECTBASE_API ARoom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoom();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	TObjectPtr<UBoxComponent> triggerBox;

	UPROPERTY()
	TObjectPtr<UMyUserWidget> widget;

	UPROPERTY()
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY()
	TObjectPtr<UCameraSettingsComponent> CameraSettings;
	

public:	
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
					  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float increment = 0.01;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float colorIntensity = 0.5;

	UPROPERTY(EditAnywhere)
	float fieldOfView = 110;
};
