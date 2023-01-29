#pragma once

#include "CoreMinimal.h"

#include "BasePlayerController.generated.h"

UCLASS()
class COREUIARCHITECTURE_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void ReceivedPlayer() override;
};