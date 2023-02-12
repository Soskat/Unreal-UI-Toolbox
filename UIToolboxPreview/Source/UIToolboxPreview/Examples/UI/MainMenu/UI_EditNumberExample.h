#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "UI_EditNumberExample.generated.h"

enum class EDialogResult : uint8;

UCLASS()
class UITOOLBOXPREVIEW_API UUI_EditNumberExample : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;

	UFUNCTION(BlueprintImplementableEvent, Category = EditNumberExample)
	void OnCurrentNumberChanged(int NewCurrentNumber);

	UFUNCTION(BlueprintCallable, Category = EditNumberExample)
	void ShowChangeNumberDialog();

	UFUNCTION(BlueprintCallable, Category = EditNumberExample)
	void QuitExample();

private:
	void SetCurrentNumber(int NewNumber);
	void OnEditNumberActionChosen(EDialogResult Result);

	UPROPERTY(EditAnywhere, Category = EditNumberExample)
	int DefaultCurrentNumber = 42;
	int CurrentNumber = 42;
};
