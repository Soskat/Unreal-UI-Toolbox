#include "UI_EditNumberExample.h"

#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "CoreUIUtils.h"
#include "DebugReturnMacros.h"
#include "Messaging/GameDialogDescriptor.h"
#include "Messaging/MessagingSubsystem.h"

#define LOCTEXT_NAMESPACE "MessagingExample"

UWidget* UUI_EditNumberExample::NativeGetDesiredFocusTarget() const
{
	return this->Button_ChangeNumber;	
}

void UUI_EditNumberExample::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetCurrentNumber(this->DefaultCurrentNumber);
}

void UUI_EditNumberExample::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(this->Button_Quit))
	{
		this->Button_Quit->OnClicked().AddUObject(this, &UUI_EditNumberExample::QuitExample);
	}
	if (IsValid(this->Button_ChangeNumber))
	{
		this->Button_ChangeNumber->OnClicked().AddUObject(this, &UUI_EditNumberExample::ShowChangeNumberDialog);
	}
}

void UUI_EditNumberExample::NativeDestruct()
{
	Super::NativeDestruct();

	if (IsValid(this->Button_Quit))
	{
		this->Button_Quit->OnClicked().RemoveAll(this);
	}
	if (IsValid(this->Button_ChangeNumber))
	{
		this->Button_ChangeNumber->OnClicked().RemoveAll(this);
	}
}

void UUI_EditNumberExample::SetCurrentNumber(int NewNumber)
{
	this->CurrentNumber = NewNumber;
	if (IsValid(this->CurrentNumberLabel))
	{
		this->CurrentNumberLabel->SetText(FText::AsNumber(this->CurrentNumber));
	}
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
	RETURN_ON_INVALID(LocalPlayer);
	auto* MessagingSubsystem = LocalPlayer->GetSubsystem<UMessagingSubsystem>();
	RETURN_ON_INVALID(MessagingSubsystem);
	const auto ResultCallback = FDialogResultDelegate::CreateUObject(this, &ThisClass::OnEditNumberActionChosen);
	MessagingSubsystem->ShowConfirmation(Descriptor, ResultCallback);
}

void UUI_EditNumberExample::OnEditNumberActionChosen(EDialogResult Result)
{
	FText BodyTextFormat = LOCTEXT("complex_dialog_2_body", "Old number {0} has been {1}. New current number is {2}.");
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

		Descriptor->PossibleActions.Add(ConfirmAction);

		const auto* LocalPlayer = GetOwningLocalPlayer();
		RETURN_ON_INVALID(LocalPlayer);
		auto* MessagingSubsystem = LocalPlayer->GetSubsystem<UMessagingSubsystem>();
		RETURN_ON_INVALID(MessagingSubsystem);
		MessagingSubsystem->ShowConfirmation(Descriptor);
		
		SetCurrentNumber(NewNumber);
	}
}

#undef LOCTEXT_NAMESPACE
