#include "Messaging/MessagingSubsystem.h"

#include "CoreUIUtils.h"
#include "GameUIManagerSubsystem.h"
#include "Messaging/MessagingUIPolicy.h"
#include "Kismet/GameplayStatics.h"
#include "NativeGameplayTags.h"
#include "Messaging/GameDialogDescriptor.h"

UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_UI_LAYER_MODAL, "UI.Layers.Modal");

void UMessagingSubsystem::ShowConfirmation(UGameDialogDescriptor* DialogDescriptor,
                                           FDialogResultDelegate ResultCallback)
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
	if (IsValid(DialogDescriptor) == false)
	{
		return;
	}
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
	if (IsValid(CurrentPolicy) == false)
	{
		return nullptr;
	}
	return CurrentPolicy->GetConfirmationDialogClass();
}

TSubclassOf<UUI_BaseDialog> UMessagingSubsystem::GetErrorDialogClass() const
{
	const auto* CurrentPolicy = GetCurrentMessagingUIPolicy();
	if (IsValid(CurrentPolicy) == false)
	{
		return nullptr;
	}
	return CurrentPolicy->GetErrorDialogClass();
}

UMessagingUIPolicy* UMessagingSubsystem::GetCurrentMessagingUIPolicy() const
{
	const auto* GameInstance = UGameplayStatics::GetGameInstance(this);
	if (IsValid(GameInstance) == false)
	{
		return nullptr;
	}
	const auto* GameUIManager = GameInstance->GetSubsystem<UGameUIManagerSubsystem>();
	if (IsValid(GameUIManager) == false)
	{
		return nullptr;
	}
	return GameUIManager->GetCurrentMessagingUIPolicy();
}
