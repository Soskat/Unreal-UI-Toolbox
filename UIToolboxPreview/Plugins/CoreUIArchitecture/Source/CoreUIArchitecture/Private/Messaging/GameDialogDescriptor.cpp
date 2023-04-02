#include "Messaging/GameDialogDescriptor.h"

#define LOCTEXT_NAMESPACE "Messaging"

TObjectPtr<UGameDialogDescriptor> UGameDialogDescriptor::CreateConfirmationOk(const FText& Header, const FText& Body)
{
	TObjectPtr<UGameDialogDescriptor> Descriptor = NewObject<UGameDialogDescriptor>();
	Descriptor->Header = Header;
	Descriptor->Body = Body;

	FGameDialogAction ConfirmAction;
	ConfirmAction.Result = EDialogResult::Confirmed;
	ConfirmAction.DisplayText = LOCTEXT("dialog_option_ok", "Ok");
	ConfirmAction.bDesiredFocusTarget = true;
	
	Descriptor->PossibleActions.Add(ConfirmAction);

	return Descriptor;
}

TObjectPtr<UGameDialogDescriptor> UGameDialogDescriptor::CreateConfirmationOkCancel(const FText& Header, const FText& Body)
{
	TObjectPtr<UGameDialogDescriptor> Descriptor = NewObject<UGameDialogDescriptor>();
	Descriptor->Header = Header;
	Descriptor->Body = Body;

	FGameDialogAction ConfirmAction;
	ConfirmAction.Result = EDialogResult::Confirmed;
	ConfirmAction.DisplayText = LOCTEXT("dialog_option_ok", "Ok");
	ConfirmAction.bDesiredFocusTarget = true;
	
	FGameDialogAction DeclineAction;
	DeclineAction.Result = EDialogResult::Declined;
	DeclineAction.DisplayText = LOCTEXT("dialog_option_cancel", "Cancel");
	
	Descriptor->PossibleActions.Add(ConfirmAction);

	return Descriptor;
}

TObjectPtr<UGameDialogDescriptor> UGameDialogDescriptor::CreateConfirmationYesNo(const FText& Header, const FText& Body)
{
	TObjectPtr<UGameDialogDescriptor> Descriptor = NewObject<UGameDialogDescriptor>();
	Descriptor->Header = Header;
	Descriptor->Body = Body;

	FGameDialogAction DeclineAction;
	DeclineAction.Result = EDialogResult::Declined;
	DeclineAction.DisplayText = LOCTEXT("dialog_option_no", "No");

	FGameDialogAction ConfirmAction;
	ConfirmAction.Result = EDialogResult::Confirmed;
	ConfirmAction.DisplayText = LOCTEXT("dialog_option_yes", "Yes");
	ConfirmAction.bDesiredFocusTarget = true;

	Descriptor->PossibleActions.Add(DeclineAction);
	Descriptor->PossibleActions.Add(ConfirmAction);

	return Descriptor;
}

#undef LOCTEXT_NAMESPACE