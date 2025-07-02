// All Rights Reserved by SweetSpot 2025-2026.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnTentacle.generated.h"

class UArrowComponent;
class UBoxComponent;

UCLASS()
class UNREALPROJECTBASE_API ASpawnTentacle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnTentacle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	TObjectPtr<UBoxComponent> triggerBox;
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UArrowComponent> spawnTentacle;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float restoreMadnessValue = 0.1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float IncreaseMadness = 0.02f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MadnessTickInterval = 0.4f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float comingUpSpeed = 2;
};
