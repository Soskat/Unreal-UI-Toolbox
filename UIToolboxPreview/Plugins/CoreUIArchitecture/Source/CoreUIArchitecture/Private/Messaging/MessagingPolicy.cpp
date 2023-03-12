#include "Messaging/MessagingPolicy.h"

TSubclassOf<UUI_BaseDialog> UMessagingPolicy::GetConfirmationDialogClass() const
{
	if (this->ConfirmationDialogClass != nullptr)
	{
		return this->ConfirmationDialogClass.LoadSynchronous();
	}
	return nullptr;
}

TSubclassOf<UUI_BaseDialog> UMessagingPolicy::GetErrorDialogClass() const
{
	if (this->ErrorDialogClass != nullptr)
	{
		return this->ErrorDialogClass.LoadSynchronous();
	}
	return nullptr;
}
