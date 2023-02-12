#pragma once

#include "CoreMinimal.h"
#include "UI_GameLayout.h"
#include "Messaging/UI_BaseDialog.h"
#include "MessagingUIPolicy.generated.h"

/**
 * This object contains a set of preferred widgets to use for a confirmation and an error dialogs.
 * It can be dynamically switched during runtime by calling proper methods from UGameUIManagerSubsystem.
 */
UCLASS(Abstract, Blueprintable, Within = GameUIManagerSubsystem)
class COREUIARCHITECTURE_API UMessagingUIPolicy : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Game UI Policy")
	TSubclassOf<UUI_BaseDialog> GetConfirmationDialogClass() const;
	
	UFUNCTION(BlueprintCallable, Category = "Game UI Policy")
	TSubclassOf<UUI_BaseDialog> GetErrorDialogClass() const;

private:
	UPROPERTY(EditAnywhere, Category = "Messaging")
	TSoftClassPtr<UUI_BaseDialog> ConfirmationDialogClass = nullptr;

	UPROPERTY(EditAnywhere, Category = "Messaging")
	TSoftClassPtr<UUI_BaseDialog> ErrorDialogClass = nullptr;
};
