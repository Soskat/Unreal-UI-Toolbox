#pragma once

#include "CoreMinimal.h"
#include "Messaging/UI_BaseDialog.h"
#include "UI_DialogWithButtons.generated.h"

class UCommonTextBlock;
class UCommonRichTextBlock;
class UDynamicEntryBox;

UCLASS(Abstract)
class COREUIARCHITECTURE_API UUI_DialogWithButtons : public UUI_BaseDialog
{
	GENERATED_BODY()

public:
	virtual void NativeSetupDialog(UGameDialogDescriptor* Descriptor, FDialogResultDelegate ResultCallback) override;

	UFUNCTION(BlueprintCallable, Category = Messaging)
	void CloseDialogWithResult(EDialogResult Result);

protected:
	virtual UWidget* NativeGetDesiredFocusTarget() const;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> HeaderTextLabel = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonRichTextBlock> BodyTextLabel = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UDynamicEntryBox> ButtonsEntryBox = nullptr;

	UPROPERTY()
	TObjectPtr<UWidget> ButtonToFocus = nullptr;
};
