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

	UPROPERTY(meta = (BindWidget))
	UCommonButtonBase* Button_ShowComplex = nullptr;
	UFUNCTION()
	void ShowComplexDialogExample();

	UPROPERTY(meta = (BindWidget))
	UCommonButtonBase* Button_OpenGameplayLevel = nullptr;
	UFUNCTION()
	void OnOpenGameplayLevelButtonClicked();

	UPROPERTY(meta = (BindWidget))
	UCommonButtonBase* Button_QuitGame = nullptr;
	UFUNCTION()
	void OnQuitGameButtonClicked();

	UPROPERTY(EditAnywhere, Category = MainMenu)
	TSubclassOf<UCommonActivatableWidget> EditNumberExampleClass = nullptr;

	UPROPERTY(EditAnywhere, Category = MainMenu)
	FName GameplayLevelName = {};
};
