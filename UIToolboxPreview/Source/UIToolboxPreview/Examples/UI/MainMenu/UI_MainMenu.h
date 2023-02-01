#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "UI_MainMenu.generated.h"

class UCommonButtonBase;

UCLASS()
class UITOOLBOXPREVIEW_API UUI_MainMenu : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	UCommonButtonBase* Button_ShowDialog = nullptr;
	UFUNCTION()
	void ShowExampleConfirmationDialog();
	
	UPROPERTY(meta = (BindWidget))
	UCommonButtonBase* Button_ShowError = nullptr;
	UFUNCTION()
	void ShowExampleErrorDialog();
};
