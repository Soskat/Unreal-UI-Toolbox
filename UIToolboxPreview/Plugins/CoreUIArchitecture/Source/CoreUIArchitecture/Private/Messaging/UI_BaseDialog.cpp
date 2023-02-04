#include "Messaging/UI_BaseDialog.h"

#include "CoreUIUtils.h"

void UUI_BaseDialog::SetupDialog(UGameDialogDescriptor* Descriptor, FDialogResultDelegate ResultCallback)
{
	this->OnResultCallback = ResultCallback;
	OnSetupDialog(Descriptor);
}

void UUI_BaseDialog::KillDialog()
{
	UCoreUIUtils::PopContentFromLayerForPlayer(GetOwningLocalPlayer(), this);
}
