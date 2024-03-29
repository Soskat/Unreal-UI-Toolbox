#pragma once

#include "CoreMinimal.h"
#include "CoreUIArchitecture/Public/BasicUI/UI_BaseActivatableWidget.h"
#include "GameDialogDescriptor.h"
#include "UI_BaseDialog.generated.h"

/**
 * Base class for a dialog popup widget.
 */
UCLASS(Abstract)
class COREUIARCHITECTURE_API UUI_BaseDialog : public UUI_BaseActivatableWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = Dialog)
	void BP_SetupDialog(UGameDialogDescriptor* Descriptor);
	virtual void NativeSetupDialog(UGameDialogDescriptor* Descriptor, FDialogResultDelegate ResultCallback);

	UFUNCTION(BlueprintImplementableEvent, Category = Dialog)
	void OnSetupDialogFinished();

	UFUNCTION(BlueprintCallable, Category = Dialog)
	virtual void KillDialog();

	FDialogResultDelegate OnResultCallback;
};
