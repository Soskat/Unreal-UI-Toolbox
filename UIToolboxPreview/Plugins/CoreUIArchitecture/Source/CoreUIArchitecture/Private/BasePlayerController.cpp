#include "BasePlayerController.h"

#include "BaseLocalPlayer.h"

void ABasePlayerController::ReceivedPlayer()
{
	Super::ReceivedPlayer();

	UBaseLocalPlayer* LocalPlayer = Cast<UBaseLocalPlayer>(this->Player);
	if (IsValid(LocalPlayer))
	{
		LocalPlayer->OnPlayerControllerSet.Broadcast(LocalPlayer, this);
	}
}
