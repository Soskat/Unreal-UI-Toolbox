#pragma once

#include "CoreMinimal.h"
#include "GameDialogDescriptor.h"
#include "Subsystems/LocalPlayerSubsystem.h"

#include "MessagingSubsystem.generated.h"

class UGameUIPolicy;
class UUI_BaseDialog;

UCLASS()
class COREUIARCHITECTURE_API UMessagingSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	void ShowConfirmation(UGameDialogDescriptor* DialogDescriptor, FMessagingResultDelegate ResultCallback = FMessagingResultDelegate());
	void ShowError(UGameDialogDescriptor* DialogDescriptor, FMessagingResultDelegate ResultCallback = FMessagingResultDelegate());

private:
	void ShowDialogInternal(UGameDialogDescriptor* DialogDescriptor, FMessagingResultDelegate ResultCallback, TSubclassOf<UUI_BaseDialog> DialogClass);
	TSubclassOf<UUI_BaseDialog> GetConfirmationDialogClass() const;
	TSubclassOf<UUI_BaseDialog> GetErrorDialogClass() const;
	UGameUIPolicy* GetCurrentUIPolicy() const;
};