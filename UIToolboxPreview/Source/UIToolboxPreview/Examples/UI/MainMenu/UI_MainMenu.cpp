#include "UI_MainMenu.h"
#include "CommonButtonBase.h"
#include "CoreUIUtils.h"
#include "DebugReturnMacros.h"
#include "NativeGameplayTags.h"
#include "Kismet/GameplayStatics.h"
#include "Messaging/GameDialogDescriptor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Messaging/MessagingSubsystem.h"

UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_UI_LAYER_MENU, "UI.Layers.Menu");

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
	if (IsValid(this->Button_ShowComplex))
	{
		this->Button_ShowComplex->OnClicked().AddUObject(this, &UUI_MainMenu::ShowComplexDialogExample);
	}
	if (IsValid(this->Button_OpenGameplayLevel))
	{
		this->Button_OpenGameplayLevel->OnClicked().AddUObject(this, &UUI_MainMenu::OnOpenGameplayLevelButtonClicked);
	}
	if (IsValid(this->Button_QuitGame))
	{
		this->Button_QuitGame->OnClicked().AddUObject(this, &UUI_MainMenu::OnQuitGameButtonClicked);
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
	if (IsValid(this->Button_OpenGameplayLevel))
	{
		this->Button_OpenGameplayLevel->OnClicked().RemoveAll(this);
	}
	if (IsValid(this->Button_QuitGame))
	{
		this->Button_QuitGame->OnClicked().RemoveAll(this);
	}
}

void UUI_MainMenu::ShowExampleConfirmationDialog()
{
	UGameDialogDescriptor* Descriptor = NewObject<UGameDialogDescriptor>();
	Descriptor->Header = LOCTEXT("simple_confirmation_dialog_header", "Example dialog");
	Descriptor->Body = LOCTEXT("simple_confirmation_dialog_body", "This is a simple example of a confiormation dialog");

	FGameDialogAction ConfirmAction;
	ConfirmAction.Result = EDialogResult::Confirmed;
	ConfirmAction.DisplayText = LOCTEXT("dialog_option_ok", "Ok");

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
	ConfirmAction.DisplayText = LOCTEXT("dialog_option_ok", "Ok");

	Descriptor->PossibleActions.Add(ConfirmAction);

	const auto* LocalPlayer = GetOwningLocalPlayer();
	RETURN_ON_INVALID(LocalPlayer);
	auto* MessagingSubsystem = LocalPlayer->GetSubsystem<UMessagingSubsystem>();
	RETURN_ON_INVALID(MessagingSubsystem);
	MessagingSubsystem->ShowError(Descriptor);
}

void UUI_MainMenu::ShowComplexDialogExample()
{
	RETURN_ON_INVALID(this->EditNumberExampleClass);
	UCoreUIUtils::PushContentToLayerForPlayer(GetOwningLocalPlayer(), TAG_UI_LAYER_MENU, this->EditNumberExampleClass);
}

void UUI_MainMenu::OnOpenGameplayLevelButtonClicked()
{
	RETURN_ON_TRUE(this->GameplayLevelName.IsNone());
	UGameplayStatics::OpenLevel(this, this->GameplayLevelName);
}

void UUI_MainMenu::OnQuitGameButtonClicked()
{
	auto* PlayerController = GetOwningPlayer();
	RETURN_ON_INVALID(PlayerController);
	UKismetSystemLibrary::QuitGame(this, PlayerController, EQuitPreference::Quit, true);
}

#undef LOCTEXT_NAMESPACE
