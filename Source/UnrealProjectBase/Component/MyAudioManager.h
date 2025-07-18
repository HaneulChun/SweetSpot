// All Rights Reserved by SweetSpot 2025-2026.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Engine.h"
#include "FMODAudioComponent.h"
#include "FMODEvent.h"
#include "MyAudioManager.generated.h"


UENUM(BlueprintType)
enum class EInteractionState : uint8
{
    Opening     UMETA(DisplayName = "Opening"),
    Closing     UMETA(DisplayName = "Closing"),
    Opened      UMETA(DisplayName = "Opened"),
    Closed      UMETA(DisplayName = "Closed")
};

USTRUCT(BlueprintType)
struct FAudioEventData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    UFMODEvent* OpeningEvent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    UFMODEvent* ClosingEvent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    UFMODEvent* OpenedEvent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    UFMODEvent* ClosedEvent;

    FAudioEventData()
    {
        OpeningEvent = nullptr;
        ClosingEvent = nullptr;
        OpenedEvent = nullptr;
        ClosedEvent = nullptr;
    }
};

UCLASS(BlueprintType, Blueprintable)
class UNREALPROJECTBASE_API ABP_AudioManager : public AActor
{
    GENERATED_BODY()
    
public:    
    ABP_AudioManager();

protected:
    virtual void BeginPlay() override;

    // FMOD Audio Component reference
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio")
    UFMODAudioComponent* AudioComponent;

    // Audio events for different interaction states
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Events")
    FAudioEventData AudioEvents;

    // Current interaction state
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio")
    EInteractionState CurrentState;

    // Volume multiplier for all audio events
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Settings", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float VolumeMultiplier;

    // Enable/disable audio debug logging
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Settings")
    bool bEnableAudioDebug;

    // Target object to follow (optional)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Settings")
    AActor* TargetObject;

    // Auto-attach to target object
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Settings")
    bool bAutoAttachToTarget;

    // Distance from target when auto-attaching
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Settings", meta = (EditCondition = "bAutoAttachToTarget"))
    FVector AttachmentOffset;

public:
    // Main function to handle interaction success and play appropriate audio
    UFUNCTION(BlueprintCallable, Category = "Audio")
    void HandleInteractionSuccess(EInteractionState NewState);

    // Play specific audio event based on interaction state
    UFUNCTION(BlueprintCallable, Category = "Audio")
    void PlayAudioForState(EInteractionState State);

    // Stop all currently playing audio
    UFUNCTION(BlueprintCallable, Category = "Audio")
    void StopAllAudio();

    // Set volume for audio events
    UFUNCTION(BlueprintCallable, Category = "Audio")
    void SetAudioVolume(float NewVolume);

    // Get current audio volume
    UFUNCTION(BlueprintCallable, Category = "Audio")
    float GetAudioVolume() const { return VolumeMultiplier; }

    // Check if audio is currently playing
    UFUNCTION(BlueprintCallable, Category = "Audio")
    bool IsAudioPlaying() const;

    // Set audio events at runtime
    UFUNCTION(BlueprintCallable, Category = "Audio")
    void SetAudioEvents(const FAudioEventData& NewAudioEvents);

    // Get current interaction state
    UFUNCTION(BlueprintCallable, Category = "Audio")
    EInteractionState GetCurrentState() const { return CurrentState; }

    // Set target object to follow
    UFUNCTION(BlueprintCallable, Category = "Audio")
    void SetTargetObject(AActor* NewTarget);

    // Attach this audio manager to target object
    UFUNCTION(BlueprintCallable, Category = "Audio")
    void AttachToTarget();

    // Detach from current target
    UFUNCTION(BlueprintCallable, Category = "Audio")
    void DetachFromTarget();

    // Blueprint Events for custom responses
    UFUNCTION(BlueprintImplementableEvent, Category = "Audio Events")
    void OnAudioStateChanged(EInteractionState NewState);

    UFUNCTION(BlueprintImplementableEvent, Category = "Audio Events") 
    void OnAudioStarted(EInteractionState State);

    UFUNCTION(BlueprintImplementableEvent, Category = "Audio Events")
    void OnAudioStopped();

private:
    // Internal function to play FMOD event
    void PlayFMODEvent(UFMODEvent* Event);

    // Debug logging function
    void LogAudioDebug(const FString& Message);

    // Update position relative to target
    void UpdateTargetPosition();
};