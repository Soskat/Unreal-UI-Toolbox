#include "GameUIManagerSubsystem.h"

#include "BaseLocalPlayer.h"
#include "CoreUIArchitectureSettings.h"
#include "Messaging/MessagingPolicy.h"
#include "NativeGameplayTags.h"
#include "UI_GameLayout.h"

void UGameUIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const UCoreUIArchitectureSettings* CoreUISettings = GetDefault<UCoreUIArchitectureSettings>();
	this->GameLayoutClass = CoreUISettings->GetGameLayoutWidgetClass();

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
	if (IsValid(BaseLocalPlayer) == false)
	{
		return nullptr;
	}
	if (this->GameLayouts.Contains(BaseLocalPlayer) == false)
	{
		return nullptr;
	}
	return this->GameLayouts[BaseLocalPlayer];
}

void UGameUIManagerSubsystem::RegisterLocalPlayer(ULocalPlayer* LocalPlayer)
{
	UBaseLocalPlayer* BaseLocalPlayer = Cast<UBaseLocalPlayer>(LocalPlayer);
	if (IsValid(BaseLocalPlayer) == false)
	{
		return;
	}
	BaseLocalPlayer->OnPlayerControllerSet.AddWeakLambda(
		this,
		[this](UBaseLocalPlayer* BaseLocalPlayer, APlayerController* PlayerController)
		{
			UnregisterLocalPlayer(BaseLocalPlayer);
			if (IsValid(this->GameLayoutClass) == false)
			{
				return;
			}
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
	if (IsValid(BaseLocalPlayer) == false)
	{
		return;
	}
	if (this->GameLayouts.Contains(BaseLocalPlayer) == false)
	{
		return;
	}
	const auto GameLayout = this->GameLayouts[BaseLocalPlayer];
	if (IsValid(GameLayout))
	{
		GameLayout->RemoveFromParent();
	}
	this->GameLayouts.Remove(BaseLocalPlayer);
}
