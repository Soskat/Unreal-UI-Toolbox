#include "UIToolboxPreview/Examples/UI/MainMenu/UI_MainMenu.h"
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
	const TObjectPtr<UGameDialogDescriptor> Descriptor = UGameDialogDescriptor::CreateConfirmationOk(
		LOCTEXT("simple_confirmation_dialog_header", "Example dialog"),
		LOCTEXT("simple_confirmation_dialog_body", "This is a simple example of a confiormation dialog"));

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
	const TObjectPtr<UGameDialogDescriptor> Descriptor = UGameDialogDescriptor::CreateConfirmationOk(
		LOCTEXT("simple_error_dialog_header", "Example error dialog"),
		LOCTEXT("simple_error_dialog_body", "This is a simple example of an error dialog"));

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
	const TObjectPtr<UGameDialogDescriptor> Descriptor = UGameDialogDescriptor::CreateConfirmationYesNo(
		LOCTEXT("open_gameplay_level_confirmation_header", "Open Gameplay Level"),
		LOCTEXT("open_gameplay_level_confirmation_body", "Do you want to open example Gameplay level?"));

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

	const FDialogResultDelegate ResultCallback = FDialogResultDelegate::CreateUObject(
		this,
		&UUI_MainMenu::HandleOpenGameplayLevelConfirmationResult);

	MessagingSubsystem->ShowConfirmation(Descriptor, ResultCallback);
}

void UUI_MainMenu::ShowConfirmationForQuitGame()
{
	const TObjectPtr<UGameDialogDescriptor> Descriptor = UGameDialogDescriptor::CreateConfirmationYesNo(
		LOCTEXT("quit_game_confirmation_header", "Quit Game"),
		LOCTEXT("quit_game_confirmation_body", "Do you want to quit game?"));

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

	const FDialogResultDelegate ResultCallback = FDialogResultDelegate::CreateUObject(
		this,
		&UUI_MainMenu::HandleQuitGameConfirmationResult);

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
