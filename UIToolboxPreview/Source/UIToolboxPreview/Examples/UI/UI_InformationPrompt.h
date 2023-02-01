#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "UI_InformationPrompt.generated.h"

class UCommonTextBlock;

UCLASS()
class UITOOLBOXPREVIEW_API UUI_InformationPrompt : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	void SetInformationText(const FText& NewText) const;

private:
	UPROPERTY(meta = (BindWidget))
	UCommonTextBlock* InformationLabel = nullptr;
};
