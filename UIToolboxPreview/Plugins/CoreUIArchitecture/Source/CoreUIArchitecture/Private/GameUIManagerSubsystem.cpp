#include "GameUIManagerSubsystem.h"

#include "BaseLocalPlayer.h"
#include "CoreUIArchitectureSettings.h"
#include "CoreUILogs.h"
#include "DebugReturnMacros.h"
#include "Messaging/MessagingUIPolicy.h"
#include "NativeGameplayTags.h"
#include "UI_GameLayout.h"

UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_UI_POLICY_DEFAULT, "UI.Policy.Default");

void UGameUIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const UCoreUIArchitectureSettings* CoreUISettings = GetDefault<UCoreUIArchitectureSettings>();
	this->GameLayoutClass = CoreUISettings->GetGameLayoutWidgetClass();

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
			                *PolicyInfo.UIPolicyTag.ToString(), *PolicyInfo.UIPolicyClass.ToString());
			continue;
		}

		this->AvailablePolicies.Add(PolicyInfo.UIPolicyTag, PolicyClass);
	}

	SetDefaultMessagingUIPolicy();

	auto* GameInstance = GetGameInstance();
	if (IsValid(GameInstance))
	{
		GameInstance->OnLocalPlayerAddedEvent.AddUObject(this, &UGameUIManagerSubsystem::RegisterLocalPlayer);
		GameInstance->OnLocalPlayerRemovedEvent.AddUObject(this, &UGameUIManagerSubsystem::UnregisterLocalPlayer);
	}
}

void UGameUIManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();

	SetMessagingUIPolicy(nullptr);

	auto* GameInstance = GetGameInstance();
	if (IsValid(GameInstance))
	{
		GameInstance->OnLocalPlayerAddedEvent.RemoveAll(this);
		GameInstance->OnLocalPlayerRemovedEvent.RemoveAll(this);
	}
}

UUI_GameLayout* UGameUIManagerSubsystem::GetGameLayoutForPlayer(ULocalPlayer* LocalPlayer)
{
	const UBaseLocalPlayer* BaseLocalPlayer = Cast<UBaseLocalPlayer>(LocalPlayer);
	RETURN_ARG_ON_INVALID(BaseLocalPlayer, nullptr);
	RETURN_ARG_ON_FALSE(this->GameLayouts.Contains(BaseLocalPlayer), nullptr);
	return this->GameLayouts[BaseLocalPlayer];
}

void UGameUIManagerSubsystem::RegisterLocalPlayer(ULocalPlayer* LocalPlayer)
{
	RETURN_ON_INVALID(this->CurrentPolicy);
	UBaseLocalPlayer* BaseLocalPlayer = Cast<UBaseLocalPlayer>(LocalPlayer);
	RETURN_ON_INVALID(BaseLocalPlayer);
	BaseLocalPlayer->OnPlayerControllerSet.AddWeakLambda(
		this,
		[this](UBaseLocalPlayer* BaseLocalPlayer, APlayerController* PlayerController)
		{
			UnregisterLocalPlayer(BaseLocalPlayer);
			RETURN_ON_INVALID(this->GameLayoutClass);
			auto* GameLayout = CreateWidget<UUI_GameLayout>(PlayerController, this->GameLayoutClass);
			if (IsValid(GameLayout))
			{
				GameLayout->AddToPlayerScreen(1000);
				this->GameLayouts.Add(BaseLocalPlayer, GameLayout);
			}
		});
}

void UGameUIManagerSubsystem::UnregisterLocalPlayer(ULocalPlayer* LocalPlayer)
{
	const UBaseLocalPlayer* BaseLocalPlayer = Cast<UBaseLocalPlayer>(LocalPlayer);
	RETURN_ON_INVALID(BaseLocalPlayer);
	RETURN_ON_FALSE(this->GameLayouts.Contains(BaseLocalPlayer));
	auto* GameLayout = this->GameLayouts[BaseLocalPlayer];
	if (IsValid(GameLayout))
	{
		GameLayout->RemoveFromParent();
	}
	this->GameLayouts.Remove(BaseLocalPlayer);
}

void UGameUIManagerSubsystem::SetMessagingUIPolicy(UMessagingUIPolicy* NewPolicy)
{
	if (this->CurrentPolicy != NewPolicy)
	{
		this->CurrentPolicy = NewPolicy;
	}
}

void UGameUIManagerSubsystem::SetMessagingUIPolicyFromTag(FGameplayTag PolicyTag)
{
	const auto* Found = this->AvailablePolicies.Find(PolicyTag);
	if (Found != nullptr)
	{
		const auto NewPolicy = NewObject<UMessagingUIPolicy>(this, *Found);
		SetMessagingUIPolicy(NewPolicy);
	}
}

void UGameUIManagerSubsystem::SetDefaultMessagingUIPolicy()
{
	SetMessagingUIPolicyFromTag(TAG_UI_POLICY_DEFAULT);
}
