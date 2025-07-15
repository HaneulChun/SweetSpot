// All Rights Reserved by SweetSpot 2025-2026.


#include "MyAudioManager.h"
#include "Components/SceneComponent.h"
#include "FMODBlueprintStatics.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

ABP_AudioManager::ABP_AudioManager()
{
    PrimaryActorTick.bCanEverTick = false;

    // Create root component
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    // Create FMOD audio component
    AudioComponent = CreateDefaultSubobject<UFMODAudioComponent>(TEXT("AudioComponent"));
    AudioComponent->SetupAttachment(RootComponent);
    
    // Initialize default values
    CurrentState = EInteractionState::Closed;
    VolumeMultiplier = 1.0f;
    bEnableAudioDebug = false;
    TargetObject = nullptr;
    bAutoAttachToTarget = false;
    AttachmentOffset = FVector(0.0f, 0.0f, 0.0f);
}

void ABP_AudioManager::BeginPlay()
{
    Super::BeginPlay();
    
    // Auto-attach to target if specified
    if (bAutoAttachToTarget && TargetObject)
    {
        AttachToTarget();
    }
    
    LogAudioDebug(TEXT("Blueprint Audio Manager initialized"));
}

void ABP_AudioManager::HandleInteractionSuccess(EInteractionState NewState)
{
    LogAudioDebug(FString::Printf(TEXT("Handling interaction success: %s -> %s"), 
        *UEnum::GetValueAsString(CurrentState), 
        *UEnum::GetValueAsString(NewState)));

    // Update current state
    EInteractionState PreviousState = CurrentState;
    CurrentState = NewState;

    // Play appropriate audio for the new state
    PlayAudioForState(NewState);

    // Call Blueprint event
    OnAudioStateChanged(NewState);
}

void ABP_AudioManager::PlayAudioForState(EInteractionState State)
{
    UFMODEvent* EventToPlay = nullptr;

    switch (State)
    {
        case EInteractionState::Opening:
            EventToPlay = AudioEvents.OpeningEvent;
            LogAudioDebug(TEXT("Playing opening audio"));
            break;
        case EInteractionState::Closing:
            EventToPlay = AudioEvents.ClosingEvent;
            LogAudioDebug(TEXT("Playing closing audio"));
            break;
        case EInteractionState::Opened:
            EventToPlay = AudioEvents.OpenedEvent;
            LogAudioDebug(TEXT("Playing opened audio"));
            break;
        case EInteractionState::Closed:
            EventToPlay = AudioEvents.ClosedEvent;
            LogAudioDebug(TEXT("Playing closed audio"));
            break;
    }

    if (EventToPlay)
    {
        PlayFMODEvent(EventToPlay);
        OnAudioStarted(State);
    }
    else
    {
        LogAudioDebug(FString::Printf(TEXT("No audio event found for state: %s"), 
            *UEnum::GetValueAsString(State)));
    }
}

void ABP_AudioManager::PlayFMODEvent(UFMODEvent* Event)
{
    if (!Event)
    {
        LogAudioDebug(TEXT("Cannot play null FMOD event"));
        return;
    }

    if (AudioComponent)
    {
        // Stop any currently playing audio
        AudioComponent->Stop();
        
        // Set the new event
        AudioComponent->SetEvent(Event);
        
        // Set volume
        AudioComponent->SetVolume(VolumeMultiplier);
        
        // Update position if following target
        UpdateTargetPosition();
        
        // Play the event
        AudioComponent->Play();
        
        LogAudioDebug(FString::Printf(TEXT("Playing FMOD event: %s"), 
            Event ? *Event->GetName() : TEXT("Unknown")));
    }
    else
    {
        LogAudioDebug(TEXT("Audio component is null, cannot play FMOD event"));
    }
}

void ABP_AudioManager::StopAllAudio()
{
    if (AudioComponent)
    {
        AudioComponent->Stop();
        LogAudioDebug(TEXT("Stopped all audio"));
        OnAudioStopped();
    }
}

void ABP_AudioManager::SetAudioVolume(float NewVolume)
{
    VolumeMultiplier = FMath::Clamp(NewVolume, 0.0f, 1.0f);
    
    if (AudioComponent)
    {
        AudioComponent->SetVolume(VolumeMultiplier);
    }
    
    LogAudioDebug(FString::Printf(TEXT("Audio volume set to: %f"), VolumeMultiplier));
}

bool ABP_AudioManager::IsAudioPlaying() const
{
    if (AudioComponent)
    {
        return AudioComponent->IsPlaying();
    }
    return false;
}

void ABP_AudioManager::SetAudioEvents(const FAudioEventData& NewAudioEvents)
{
    AudioEvents = NewAudioEvents;
    LogAudioDebug(TEXT("Audio events updated"));
}

void ABP_AudioManager::SetTargetObject(AActor* NewTarget)
{
    TargetObject = NewTarget;
    LogAudioDebug(FString::Printf(TEXT("Target object set to: %s"), 
        NewTarget ? *NewTarget->GetName() : TEXT("None")));
}

void ABP_AudioManager::AttachToTarget()
{
    if (TargetObject)
    {
        // Attach to target's root component
        AttachToActor(TargetObject, FAttachmentTransformRules::KeepWorldTransform);
        
        // Apply offset
        SetActorRelativeLocation(AttachmentOffset);
        
        LogAudioDebug(FString::Printf(TEXT("Attached to target: %s"), *TargetObject->GetName()));
    }
    else
    {
        LogAudioDebug(TEXT("Cannot attach: No target object specified"));
    }
}

void ABP_AudioManager::DetachFromTarget()
{
    DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
    LogAudioDebug(TEXT("Detached from target"));
}

void ABP_AudioManager::UpdateTargetPosition()
{
    if (TargetObject && !GetAttachParentActor())
    {
        // If not attached but has target, update position to follow target
        FVector TargetLocation = TargetObject->GetActorLocation() + AttachmentOffset;
        SetActorLocation(TargetLocation);
    }
}

void ABP_AudioManager::LogAudioDebug(const FString& Message)
{
    if (bEnableAudioDebug)
    {
        UE_LOG(LogTemp, Warning, TEXT("[BP_AudioManager] %s"), *Message);
        
        // Also display on screen if in development
        if (GEngine && GetWorld())
        {
            GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Cyan, 
                FString::Printf(TEXT("[BP_AudioManager] %s"), *Message));
        }
    }
}