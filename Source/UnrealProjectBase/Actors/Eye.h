// All Rights Reserved by SweetSpot 2025-2026.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Eye.generated.h"

UCLASS()
class UNREALPROJECTBASE_API AEye : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEye();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
