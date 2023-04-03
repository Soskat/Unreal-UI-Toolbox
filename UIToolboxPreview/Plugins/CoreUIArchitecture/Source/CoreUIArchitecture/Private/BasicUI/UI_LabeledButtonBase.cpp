#include "BasicUI/UI_LabeledButtonBase.h"

#include "CommonTextBlock.h"

void UUI_LabeledButtonBase::SetLabelText(const FText& NewText)
{
	if (IsValid(this->TextLabel))
	{
		this->TextLabel->SetText(NewText);
	}
}
