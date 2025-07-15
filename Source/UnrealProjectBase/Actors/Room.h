// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"

#include "Room.generated.h"

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

	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	TObjectPtr<UBoxComponent> triggerBox;

	UPROPERTY()
	TObjectPtr<UMyUserWidget> widget;

	UPROPERTY()
	TObjectPtr<UCameraComponent> Camera;


	UPROPERTY(EditAnywhere)
	float duration = 1.0f;
	UPROPERTY()
	float ElapsedTime = 0.0f;
	
	UPROPERTY()
	float startColor = 1.0f;
	UPROPERTY()
	float endColor = 0.0f;

	UPROPERTY()
	float startVignette = 1.0f;
	UPROPERTY()
	float endVignette = 0.0f;
public:	
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
					  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	void Color(float intensity, float Vignette);

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float increment = 0.01;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float colorIntensity = 0.5;
};
