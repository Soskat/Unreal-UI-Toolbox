#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "UI_EditNumberExample.generated.h"

enum class EDialogResult : uint8;
class UCommonTextBlock;
class UCommonButtonBase;

UCLASS()
class UITOOLBOXPREVIEW_API UUI_EditNumberExample : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	virtual UWidget* NativeGetDesiredFocusTarget() const override;

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	void SetCurrentNumber(int NewNumber);
	void OnEditNumberActionChosen(EDialogResult Result);
	
	UPROPERTY(meta = (BindWidget))
	UCommonTextBlock* CurrentNumberLabel = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	UCommonButtonBase* Button_Quit = nullptr;
	UFUNCTION()
	void QuitExample();
	
	UPROPERTY(meta = (BindWidget))
	UCommonButtonBase* Button_ChangeNumber = nullptr;
	UFUNCTION()
	void ShowChangeNumberDialog();

	UPROPERTY(EditAnywhere, Category = EditNumberExample)
	int DefaultCurrentNumber = 42;
	int CurrentNumber = 42;
};
