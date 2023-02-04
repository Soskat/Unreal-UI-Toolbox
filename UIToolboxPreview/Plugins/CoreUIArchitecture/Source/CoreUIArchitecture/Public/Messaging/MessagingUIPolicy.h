#pragma once

#include "CoreMinimal.h"
#include "UI_GameLayout.h"
#include "Messaging/UI_BaseDialog.h"
#include "MessagingUIPolicy.generated.h"

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
