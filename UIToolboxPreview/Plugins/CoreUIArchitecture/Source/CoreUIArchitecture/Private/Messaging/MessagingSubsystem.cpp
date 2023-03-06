#include "Messaging/MessagingSubsystem.h"

#include "CoreUIArchitectureSettings.h"
#include "CoreUILogs.h"
#include "CoreUIUtils.h"
#include "Messaging/MessagingPolicy.h"
#include "Kismet/GameplayStatics.h"
#include "NativeGameplayTags.h"
#include "Messaging/GameDialogDescriptor.h"

UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_UI_LAYER_MODAL, "UI.Layers.Modal");
UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_UI_POLICY_DEFAULT, "UI.Policy.Default");

void UMessagingSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const UCoreUIArchitectureSettings* CoreUISettings = GetDefault<UCoreUIArchitectureSettings>();

	for (auto& PolicyInfo : CoreUISettings->AvailableUIPolicies)
	{
		if (PolicyInfo.UIPolicyTag.IsValid() == false)
		{
			CORE_UI_WARNING("Policy with invalid tag has been detected - rejecting.");
			continue;
		}
		const auto PolicyClass = PolicyInfo.UIPolicyClass.LoadSynchronous();
		if (PolicyClass == nullptr)
		{
			CORE_UI_WARNING("None class set for policy with tag %s", *PolicyInfo.UIPolicyTag.ToString());
			continue;
		}

		if (this->AvailablePolicies.Contains(PolicyInfo.UIPolicyTag))
		{
			CORE_UI_WARNING("Policy with tag %s has already been registered (item: %s)",
				*PolicyInfo.UIPolicyTag.ToString(),
				*PolicyInfo.UIPolicyClass.ToString());
			continue;
		}

		this->AvailablePolicies.Add(PolicyInfo.UIPolicyTag, PolicyClass);
	}

	SetDefaultMessagingPolicy();
}

void UMessagingSubsystem::Deinitialize()
{
	Super::Deinitialize();

	SetMessagingPolicy(nullptr);
}

void UMessagingSubsystem::SetMessagingPolicy(UMessagingPolicy* NewPolicy)
{
	if (this->CurrentPolicy != NewPolicy)
	{
		this->CurrentPolicy = NewPolicy;
	}
}

void UMessagingSubsystem::SetMessagingPolicyFromTag(FGameplayTag PolicyTag)
{
	const auto* Found = this->AvailablePolicies.Find(PolicyTag);
	if (Found != nullptr)
	{
		const auto NewPolicy = NewObject<UMessagingPolicy>(this, *Found);
		SetMessagingPolicy(NewPolicy);
	}
}

void UMessagingSubsystem::SetDefaultMessagingPolicy()
{
	SetMessagingPolicyFromTag(TAG_UI_POLICY_DEFAULT);
}

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
			NewDialog->NativeSetupDialog(DialogDescriptor, ResultCallback);
		}
	}
}

TSubclassOf<UUI_BaseDialog> UMessagingSubsystem::GetConfirmationDialogClass() const
{
	if (IsValid(this->CurrentPolicy) == false)
	{
		return nullptr;
	}
	return CurrentPolicy->GetConfirmationDialogClass();
}

TSubclassOf<UUI_BaseDialog> UMessagingSubsystem::GetErrorDialogClass() const
{
	if (IsValid(this->CurrentPolicy) == false)
	{
		return nullptr;
	}
	return CurrentPolicy->GetErrorDialogClass();
}
