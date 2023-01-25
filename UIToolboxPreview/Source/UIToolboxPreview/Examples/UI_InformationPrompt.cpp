#include "UI_InformationPrompt.h"

#include "CommonTextBlock.h"

void UUI_InformationPrompt::SetInformationText(const FText& NewText) const
{
	if (IsValid(this->InformationLabel))
	{
		this->InformationLabel->SetText(NewText);
	}
}
