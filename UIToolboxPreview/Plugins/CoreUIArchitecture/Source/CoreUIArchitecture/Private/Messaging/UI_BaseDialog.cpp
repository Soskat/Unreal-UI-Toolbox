#include "Messaging/UI_BaseDialog.h"

#include "CoreUIUtils.h"

void UUI_BaseDialog::NativeSetupDialog(UGameDialogDescriptor* Descriptor, FDialogResultDelegate ResultCallback)
{
	this->OnResultCallback = ResultCallback;
	BP_SetupDialog(Descriptor);
	OnSetupDialogFinished();
}

void UUI_BaseDialog::KillDialog()
{
	UCoreUIUtils::PopContentFromLayerForPlayer(GetOwningLocalPlayer(), this);
}
