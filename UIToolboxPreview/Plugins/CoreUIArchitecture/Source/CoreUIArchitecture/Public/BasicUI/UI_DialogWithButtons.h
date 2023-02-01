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
	virtual void SetupDialog(UGameDialogDescriptor* Descriptor, FMessagingResultDelegate ResultCallback) override;

private:
	UFUNCTION()
	void CloseDialogWithResult(EDialogResult Result);
	
	UPROPERTY(meta = (BindWidget))
	UCommonTextBlock* HeaderTextLabel = nullptr;

	UPROPERTY(meta = (BindWidget))
	UCommonRichTextBlock* BodyTextLabel = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	UDynamicEntryBox* ButtonsEntryBox = nullptr;
};
