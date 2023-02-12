#pragma once

#include "CoreMinimal.h"
#include "Engine/LocalPlayer.h"

#include "BaseLocalPlayer.generated.h"

/**
 * Base class for local player, that helps UGameUIManagerSubsystem detect addition of new local player.
 */
UCLASS()
class COREUIARCHITECTURE_API UBaseLocalPlayer : public ULocalPlayer
{
	GENERATED_BODY()

public:
	/** Called when the local player is assigned a player controller */
	DECLARE_MULTICAST_DELEGATE_TwoParams(FPlayerControllerSetDelegate, UBaseLocalPlayer* LocalPlayer, APlayerController* PlayerController);
	FPlayerControllerSetDelegate OnPlayerControllerSet;
};