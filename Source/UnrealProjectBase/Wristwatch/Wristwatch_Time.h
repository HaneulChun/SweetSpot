// All Rights Reserved by SweetSpot 2025-2026.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TextRenderActor.h"
#include "Wristwatch_Time.generated.h"

UCLASS()
class UNREALPROJECTBASE_API AWristwatch_Time : public ATextRenderActor
{
	GENERATED_BODY()

public:
	AWristwatch_Time();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	void UpdateTimeDisplay() const;

	float TimeUpdateInterval = 1.0f;  // Update every second
	float TimeSinceLastUpdate = 0.0f;
};
