#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "UI_LabeledButtonBase.generated.h"

class UCommonTextBlock;

UCLASS(Abstract)
class COREUIARCHITECTURE_API UUI_LabeledButtonBase : public UCommonButtonBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = LabeledButton)
	void SetLabelText(const FText& NewText);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> TextLabel = nullptr;
};
