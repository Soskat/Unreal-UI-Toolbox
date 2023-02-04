#include "BasicUI/UI_DialogWithButtons.h"

#include "CommonButtonBase.h"
#include "CommonRichTextBlock.h"
#include "CommonTextBlock.h"
#include "BasicUI/UI_LabeledButtonBase.h"
#include "Components/DynamicEntryBox.h"

void UUI_DialogWithButtons::SetupDialog(UGameDialogDescriptor* Descriptor, FDialogResultDelegate ResultCallback)
{
	Super::SetupDialog(Descriptor, ResultCallback);

	if (IsValid(this->HeaderTextLabel))
	{
		this->HeaderTextLabel->SetText(Descriptor->Header);
	}
	if (IsValid(this->BodyTextLabel))
	{
		this->BodyTextLabel->SetText(Descriptor->Body);
	}

	if (IsValid(this->ButtonsEntryBox))
	{
		this->ButtonsEntryBox->Reset<UUI_LabeledButtonBase>([](const UUI_LabeledButtonBase& Button)
		{
			Button.OnClicked().Clear();
		});

		for (FGameDialogAction Action : Descriptor->PossibleActions)
		{
			UUI_LabeledButtonBase* Button = this->ButtonsEntryBox->CreateEntry<UUI_LabeledButtonBase>();
			Button->OnClicked().AddUObject(this, &ThisClass::CloseDialogWithResult, Action.Result);
			Button->SetLabelText(Action.DisplayText);
		}
	}
}

void UUI_DialogWithButtons::CloseDialogWithResult(EDialogResult Result)
{
	KillDialog();
	this->OnResultCallback.ExecuteIfBound(Result);
}
