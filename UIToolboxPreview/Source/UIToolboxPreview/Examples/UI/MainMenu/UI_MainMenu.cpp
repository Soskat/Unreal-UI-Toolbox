#include "UI_MainMenu.h"
#include "CommonButtonBase.h"
#include "DebugReturnMacros.h"
#include "Messaging/GameDialogDescriptor.h"
#include "Messaging/MessagingSubsystem.h"

#define LOCTEXT_NAMESPACE "MessagingExample"

void UUI_MainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(this->Button_ShowDialog))
	{
		this->Button_ShowDialog->OnClicked().AddUObject(this, &UUI_MainMenu::ShowExampleConfirmationDialog);
	}
	if (IsValid(this->Button_ShowError))
	{
		this->Button_ShowError->OnClicked().AddUObject(this, &UUI_MainMenu::ShowExampleErrorDialog);
	}
}

void UUI_MainMenu::NativeDestruct()
{
	Super::NativeDestruct();

	if (IsValid(this->Button_ShowDialog))
	{
		this->Button_ShowDialog->OnClicked().RemoveAll(this);
	}
	if (IsValid(this->Button_ShowError))
	{
		this->Button_ShowError->OnClicked().RemoveAll(this);
	}
}

void UUI_MainMenu::ShowExampleConfirmationDialog()
{
	UGameDialogDescriptor* Descriptor = NewObject<UGameDialogDescriptor>();
	Descriptor->Header = LOCTEXT("simple_confirmation_dialog_header", "Example dialog");
	Descriptor->Body = LOCTEXT("simple_confirmation_dialog_body", "This is a simple example of a confiormation dialog");

	FGameDialogAction ConfirmAction;
	ConfirmAction.Result = EDialogResult::Confirmed;
	ConfirmAction.DisplayText = LOCTEXT("simple_dialog_option", "Ok");

	Descriptor->PossibleActions.Add(ConfirmAction);

	const auto* LocalPlayer = GetOwningLocalPlayer();
	RETURN_ON_INVALID(LocalPlayer);
	auto* MessagingSubsystem = LocalPlayer->GetSubsystem<UMessagingSubsystem>();
	RETURN_ON_INVALID(MessagingSubsystem);
	MessagingSubsystem->ShowConfirmation(Descriptor);
}

void UUI_MainMenu::ShowExampleErrorDialog()
{
	UGameDialogDescriptor* Descriptor = NewObject<UGameDialogDescriptor>();
	Descriptor->Header = LOCTEXT("simple_error_dialog_header", "Example error dialog");
	Descriptor->Body = LOCTEXT("simple_error_dialog_body", "This is a simple example of an error dialog");

	FGameDialogAction ConfirmAction;
	ConfirmAction.Result = EDialogResult::Confirmed;
	ConfirmAction.DisplayText = LOCTEXT("simple_dialog_option", "Ok");

	Descriptor->PossibleActions.Add(ConfirmAction);

	const auto* LocalPlayer = GetOwningLocalPlayer();
	RETURN_ON_INVALID(LocalPlayer);
	auto* MessagingSubsystem = LocalPlayer->GetSubsystem<UMessagingSubsystem>();
	RETURN_ON_INVALID(MessagingSubsystem);
	MessagingSubsystem->ShowError(Descriptor);
}

#undef LOCTEXT_NAMESPACE
