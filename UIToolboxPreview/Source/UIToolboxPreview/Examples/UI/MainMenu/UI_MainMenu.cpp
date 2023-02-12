#include "UI_MainMenu.h"
#include "CommonButtonBase.h"
#include "CoreUIUtils.h"
#include "NativeGameplayTags.h"
#include "Kismet/GameplayStatics.h"
#include "Messaging/GameDialogDescriptor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Messaging/MessagingSubsystem.h"

UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_UI_LAYER_MENU, "UI.Layers.Menu");

#define LOCTEXT_NAMESPACE "MessagingExample"

void UUI_MainMenu::ShowConfirmationDialogExample() const
{
	UGameDialogDescriptor* Descriptor = NewObject<UGameDialogDescriptor>();
	Descriptor->Header = LOCTEXT("simple_confirmation_dialog_header", "Example dialog");
	Descriptor->Body = LOCTEXT("simple_confirmation_dialog_body", "This is a simple example of a confiormation dialog");

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
}

void UUI_MainMenu::ShowErrorDialogExample() const
{
	UGameDialogDescriptor* Descriptor = NewObject<UGameDialogDescriptor>();
	Descriptor->Header = LOCTEXT("simple_error_dialog_header", "Example error dialog");
	Descriptor->Body = LOCTEXT("simple_error_dialog_body", "This is a simple example of an error dialog");

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
	MessagingSubsystem->ShowError(Descriptor);
}

void UUI_MainMenu::ShowComplexDialogExample() const
{
	if (IsValid(this->EditNumberExampleClass) == false)
	{
		return;
	}
	UCoreUIUtils::PushContentToLayerForPlayer(GetOwningLocalPlayer(), TAG_UI_LAYER_MENU, this->EditNumberExampleClass);
}

void UUI_MainMenu::ShowConfirmationForOpenGameplayLevel()
{
	UGameDialogDescriptor* Descriptor = NewObject<UGameDialogDescriptor>();
	Descriptor->Header = LOCTEXT("open_gameplay_level_confirmation_header", "Open Gameplay Level");
	Descriptor->Body = LOCTEXT("open_gameplay_level_confirmation_body", "Do you want to open example Gameplay level?");

	FGameDialogAction DeclineAction;
	DeclineAction.Result = EDialogResult::Declined;
	DeclineAction.DisplayText = LOCTEXT("dialog_option_no", "No");

	FGameDialogAction ConfirmAction;
	ConfirmAction.Result = EDialogResult::Confirmed;
	ConfirmAction.DisplayText = LOCTEXT("dialog_option_yes", "Yes");
	ConfirmAction.bDesiredFocusTarget = true;

	Descriptor->PossibleActions.Add(DeclineAction);
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
	FDialogResultDelegate ResultCallback = FDialogResultDelegate::CreateUObject(
		this, &UUI_MainMenu::HandleOpenGameplayLevelConfirmationResult);
	MessagingSubsystem->ShowConfirmation(Descriptor, ResultCallback);
}

void UUI_MainMenu::ShowConfirmationForQuitGame()
{
	UGameDialogDescriptor* Descriptor = NewObject<UGameDialogDescriptor>();
	Descriptor->Header = LOCTEXT("quit_game_confirmation_header", "Quit Game");
	Descriptor->Body = LOCTEXT("quit_game_confirmation_body", "Do you want to quit game?");

	FGameDialogAction DeclineAction;
	DeclineAction.Result = EDialogResult::Declined;
	DeclineAction.DisplayText = LOCTEXT("dialog_option_no", "No");
	DeclineAction.bDesiredFocusTarget = true;

	FGameDialogAction ConfirmAction;
	ConfirmAction.Result = EDialogResult::Confirmed;
	ConfirmAction.DisplayText = LOCTEXT("dialog_option_yes", "Yes");

	Descriptor->PossibleActions.Add(DeclineAction);
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
	FDialogResultDelegate ResultCallback = FDialogResultDelegate::CreateUObject(
		this, &UUI_MainMenu::HandleQuitGameConfirmationResult);
	MessagingSubsystem->ShowConfirmation(Descriptor, ResultCallback);
}

void UUI_MainMenu::HandleOpenGameplayLevelConfirmationResult(EDialogResult Result)
{
	if (Result != EDialogResult::Confirmed)
	{
		return;
	}
	if (this->GameplayLevelName.IsNone() == false)
	{
		UGameplayStatics::OpenLevel(this, this->GameplayLevelName);
	}
}

void UUI_MainMenu::HandleQuitGameConfirmationResult(EDialogResult Result)
{
	if (Result != EDialogResult::Confirmed)
	{
		return;
	}
	auto* PlayerController = GetOwningPlayer();
	if (IsValid(PlayerController))
	{
		UKismetSystemLibrary::QuitGame(this, PlayerController, EQuitPreference::Quit, true);
	}
}

#undef LOCTEXT_NAMESPACE
