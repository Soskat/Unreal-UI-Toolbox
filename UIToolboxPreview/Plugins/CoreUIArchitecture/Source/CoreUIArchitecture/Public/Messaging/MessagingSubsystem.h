#pragma once

#include "CoreMinimal.h"
#include "GameDialogDescriptor.h"
#include "Subsystems/LocalPlayerSubsystem.h"

#include "MessagingSubsystem.generated.h"

class UMessagingUIPolicy;
class UUI_BaseDialog;

UCLASS()
class COREUIARCHITECTURE_API UMessagingSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	void ShowConfirmation(UGameDialogDescriptor* DialogDescriptor, FDialogResultDelegate ResultCallback = FDialogResultDelegate());
	void ShowError(UGameDialogDescriptor* DialogDescriptor, FDialogResultDelegate ResultCallback = FDialogResultDelegate());

private:
	void ShowDialogInternal(UGameDialogDescriptor* DialogDescriptor, FDialogResultDelegate ResultCallback, TSubclassOf<UUI_BaseDialog> DialogClass);
	TSubclassOf<UUI_BaseDialog> GetConfirmationDialogClass() const;
	TSubclassOf<UUI_BaseDialog> GetErrorDialogClass() const;
	UMessagingUIPolicy* GetCurrentMessagingUIPolicy() const;
};