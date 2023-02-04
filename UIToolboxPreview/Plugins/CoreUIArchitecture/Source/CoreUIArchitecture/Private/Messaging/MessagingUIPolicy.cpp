#include "Messaging/MessagingUIPolicy.h"

TSubclassOf<UUI_BaseDialog> UMessagingUIPolicy::GetConfirmationDialogClass() const
{
	if (this->ConfirmationDialogClass != nullptr)
	{
		return this->ConfirmationDialogClass.LoadSynchronous();
	}
	return nullptr;
}

TSubclassOf<UUI_BaseDialog> UMessagingUIPolicy::GetErrorDialogClass() const
{
	if (this->ErrorDialogClass != nullptr)
	{
		return this->ErrorDialogClass.LoadSynchronous();
	}
	return nullptr;
}
