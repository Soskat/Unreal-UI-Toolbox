#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "GameDialogDescriptor.h"
#include "UI_BaseDialog.generated.h"

/**
 * Base class for a dialog popup widget.
 */
UCLASS(Abstract)
class COREUIARCHITECTURE_API UUI_BaseDialog : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	virtual void SetupDialog(UGameDialogDescriptor* Descriptor, FDialogResultDelegate ResultCallback);

	UFUNCTION(BlueprintCallable, Category = Dialog)
	virtual void KillDialog();

	UFUNCTION(BlueprintImplementableEvent)
	void OnSetupDialog(UGameDialogDescriptor* Descriptor);

	FDialogResultDelegate OnResultCallback;
};
