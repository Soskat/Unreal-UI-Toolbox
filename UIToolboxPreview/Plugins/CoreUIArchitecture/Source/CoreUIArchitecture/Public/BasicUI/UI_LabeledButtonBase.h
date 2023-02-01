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
	void SetLabelText(FText& NewText);

private:
	UPROPERTY(meta = (BindWidget))
	UCommonTextBlock* TextLabel = nullptr;
};
