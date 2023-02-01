#include "GameUIPolicy.h"

TSubclassOf<UUI_GameLayout> UGameUIPolicy::GetGameLayoutWidgetClass() const
{
	return this->GameLayoutWidgetClass.LoadSynchronous();
}

TSubclassOf<UUI_BaseDialog> UGameUIPolicy::GetConfirmationDialogClass() const
{
	return this->ConfirmationDialogClass.LoadSynchronous();
}

TSubclassOf<UUI_BaseDialog> UGameUIPolicy::GetErrorDialogClass() const
{
	return this->ErrorDialogClass.LoadSynchronous();
}
