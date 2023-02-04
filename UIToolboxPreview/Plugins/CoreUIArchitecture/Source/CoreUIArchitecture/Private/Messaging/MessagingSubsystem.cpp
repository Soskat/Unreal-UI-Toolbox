#include "Messaging/MessagingSubsystem.h"

#include "CoreUIUtils.h"
#include "DebugReturnMacros.h"
#include "GameUIManagerSubsystem.h"
#include "Messaging/MessagingUIPolicy.h"
#include "Kismet/GameplayStatics.h"
#include "NativeGameplayTags.h"
#include "Messaging/GameDialogDescriptor.h"

UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_UI_LAYER_MODAL, "UI.Layers.Modal");

void UMessagingSubsystem::ShowConfirmation(UGameDialogDescriptor* DialogDescriptor, FDialogResultDelegate ResultCallback)
{
	ShowDialogInternal(DialogDescriptor, ResultCallback, GetConfirmationDialogClass());
}

void UMessagingSubsystem::ShowError(UGameDialogDescriptor* DialogDescriptor, FDialogResultDelegate ResultCallback)
{
	ShowDialogInternal(DialogDescriptor, ResultCallback, GetErrorDialogClass());
}

void UMessagingSubsystem::ShowDialogInternal(UGameDialogDescriptor* DialogDescriptor,
	FDialogResultDelegate ResultCallback,
	TSubclassOf<UUI_BaseDialog> DialogClass)
{
	RETURN_ON_INVALID(DialogDescriptor);
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer<ULocalPlayer>())
	{
		auto* NewWidget = UCoreUIUtils::PushContentToLayerForPlayer(LocalPlayer, TAG_UI_LAYER_MODAL, DialogClass);
		if (auto* NewDialog = Cast<UUI_BaseDialog>(NewWidget))
		{
			NewDialog->SetupDialog(DialogDescriptor, ResultCallback);
		}
	}
}

TSubclassOf<UUI_BaseDialog> UMessagingSubsystem::GetConfirmationDialogClass() const
{
	const auto* CurrentPolicy = GetCurrentMessagingUIPolicy();
	RETURN_ARG_ON_INVALID(CurrentPolicy, nullptr);
	return CurrentPolicy->GetConfirmationDialogClass();
}

TSubclassOf<UUI_BaseDialog> UMessagingSubsystem::GetErrorDialogClass() const
{
	const auto* CurrentPolicy = GetCurrentMessagingUIPolicy();
	RETURN_ARG_ON_INVALID(CurrentPolicy, nullptr);
	return CurrentPolicy->GetErrorDialogClass();
}

UMessagingUIPolicy* UMessagingSubsystem::GetCurrentMessagingUIPolicy() const
{
	const auto* GameInstance = UGameplayStatics::GetGameInstance(this);
	RETURN_ARG_ON_INVALID(GameInstance, nullptr);
	const auto* GameUIManager = GameInstance->GetSubsystem<UGameUIManagerSubsystem>();
	RETURN_ARG_ON_INVALID(GameUIManager, nullptr);
	return GameUIManager->GetCurrentMessagingUIPolicy();
}
