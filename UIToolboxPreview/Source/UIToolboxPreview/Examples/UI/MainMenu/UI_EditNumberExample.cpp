#include "UI_EditNumberExample.h"

#include "CoreUIUtils.h"
#include "Messaging/GameDialogDescriptor.h"
#include "Messaging/MessagingSubsystem.h"

#define LOCTEXT_NAMESPACE "MessagingExample"

void UUI_EditNumberExample::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetCurrentNumber(this->DefaultCurrentNumber);
}

void UUI_EditNumberExample::SetCurrentNumber(int NewNumber)
{
	this->CurrentNumber = NewNumber;
	OnCurrentNumberChanged(this->CurrentNumber);
}

void UUI_EditNumberExample::QuitExample()
{
	UCoreUIUtils::PopContentFromLayerForPlayer(GetOwningLocalPlayer(), this);
}

void UUI_EditNumberExample::ShowChangeNumberDialog()
{
	UGameDialogDescriptor* Descriptor = NewObject<UGameDialogDescriptor>();
	Descriptor->Header = LOCTEXT("complex_dialog_1_header", "Change number");
	const auto TextFormat = LOCTEXT("complex_dialog_1_body", "Current number is {0} - what do you want to do?");
	Descriptor->Body = FText::Format(TextFormat, FText::AsNumber(this->CurrentNumber));

	FGameDialogAction CancelAction;
	CancelAction.Result = EDialogResult::Cancelled;
	CancelAction.DisplayText = LOCTEXT("dialog_option_cancel", "Cancel");
	CancelAction.bDesiredFocusTarget = true;

	FGameDialogAction IncreaseAction;
	IncreaseAction.Result = EDialogResult::Confirmed;
	IncreaseAction.DisplayText = LOCTEXT("dialog_option_increase", "Increase");

	FGameDialogAction DecreaseAction;
	DecreaseAction.Result = EDialogResult::Declined;
	DecreaseAction.DisplayText = LOCTEXT("dialog_option_decrease", "Decrease");

	Descriptor->PossibleActions.Add(CancelAction);
	Descriptor->PossibleActions.Add(IncreaseAction);
	Descriptor->PossibleActions.Add(DecreaseAction);

	const auto* LocalPlayer = GetOwningLocalPlayer();
	if (IsValid(LocalPlayer) == false)
	{
		return;
	}
	auto* MessagingSubsystem = LocalPlayer->GetSubsystem<UMessagingSubsystem>();
	if (IsValid(MessagingSubsystem) == false)
	{
		return;
	}
	const auto ResultCallback = FDialogResultDelegate::CreateUObject(this, &ThisClass::OnEditNumberActionChosen);
	MessagingSubsystem->ShowConfirmation(Descriptor, ResultCallback);
}

void UUI_EditNumberExample::OnEditNumberActionChosen(EDialogResult Result)
{
	const FText BodyTextFormat = LOCTEXT("complex_dialog_2_body",
	                                     "Old number {0} has been {1}. New current number is {2}.");
	FText PerformedOperationText = {};
	int NewNumber = this->CurrentNumber;
	bool bNumberChanged = true;
	if (Result == EDialogResult::Confirmed)
	{
		PerformedOperationText = LOCTEXT("complex_dialog_2_increased", "increased");
		NewNumber++;
	}
	else if (Result == EDialogResult::Declined)
	{
		PerformedOperationText = LOCTEXT("complex_dialog_2_decreased", "decreased");
		NewNumber--;
	}
	else
	{
		bNumberChanged = false;
	}

	if (bNumberChanged)
	{
		UGameDialogDescriptor* Descriptor = NewObject<UGameDialogDescriptor>();
		Descriptor->Header = LOCTEXT("complex_dialog_2_header", "Number has changed");
		Descriptor->Body = FText::Format(BodyTextFormat,
		                                 FText::AsNumber(this->CurrentNumber),
		                                 PerformedOperationText,
		                                 FText::AsNumber(NewNumber));

		FGameDialogAction ConfirmAction;
		ConfirmAction.Result = EDialogResult::Confirmed;
		ConfirmAction.DisplayText = LOCTEXT("dialog_option_ok", "Ok");
		ConfirmAction.bDesiredFocusTarget = true;

		Descriptor->PossibleActions.Add(ConfirmAction);

		const auto* LocalPlayer = GetOwningLocalPlayer();
		if (IsValid(LocalPlayer) == false)
		{
			return;
		}
		auto* MessagingSubsystem = LocalPlayer->GetSubsystem<UMessagingSubsystem>();
		if (IsValid(MessagingSubsystem) == false)
		{
			return;
		}
		MessagingSubsystem->ShowConfirmation(Descriptor);

		SetCurrentNumber(NewNumber);
	}
}

#undef LOCTEXT_NAMESPACE
