#pragma once

#include "CoreMinimal.h"

#include "BasePlayerController.generated.h"

/**
 * Base class for player controller, that helps UGameUIManagerSubsystem detect addition of new local player.
 */
UCLASS()
class COREUIARCHITECTURE_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void ReceivedPlayer() override;
};