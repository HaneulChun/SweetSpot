// All Rights Reserved by SweetSpot 2025-2026.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SweetSpotGameMode.generated.h"

class UFadeObjectComponent;
/**
 * 
 */
UCLASS()
class UNREALPROJECTBASE_API ASweetSpotGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	TObjectPtr<UFadeObjectComponent> FadeObject;
	
public:

	UFUNCTION()
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void CheckForSubLevel(const TSoftObjectPtr<UWorld>& UnloadSubLevel);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UnloadThenLoadLevel(const TSoftObjectPtr<UWorld>& UnloadSubLevel, const TSoftObjectPtr<UWorld>& loadSubLevel);
	
	UFUNCTION(BlueprintCallable)
	void SetLevel();
};
