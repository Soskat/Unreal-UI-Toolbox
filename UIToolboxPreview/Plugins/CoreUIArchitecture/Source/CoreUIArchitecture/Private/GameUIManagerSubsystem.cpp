#include "GameUIManagerSubsystem.h"

#include "BaseLocalPlayer.h"
#include "CoreUIArchitectureSettings.h"
#include "DebugReturnMacros.h"
#include "GameUIPolicy.h"
#include "UI_GameLayout.h"

void UGameUIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const UCoreUIArchitectureSettings* CoreUISettings = GetDefault<UCoreUIArchitectureSettings>();
	const auto DefaultPolicyClass = CoreUISettings->GetDefaultUIPolicyClass();

	if (CurrentUIPolicy == nullptr && DefaultPolicyClass != nullptr)
	{
		SetGameUIPolicy(NewObject<UGameUIPolicy>(this, DefaultPolicyClass));
	}

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

	SetGameUIPolicy(nullptr);

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
	RETURN_ON_INVALID(this->CurrentUIPolicy);
	UBaseLocalPlayer* BaseLocalPlayer = Cast<UBaseLocalPlayer>(LocalPlayer);
	RETURN_ON_INVALID(BaseLocalPlayer);
	BaseLocalPlayer->OnPlayerControllerSet.AddWeakLambda(this,
		[this](UBaseLocalPlayer* BaseLocalPlayer, APlayerController* PlayerController)
		{
			UnregisterLocalPlayer(BaseLocalPlayer);

			const auto LayoutClass = this->CurrentUIPolicy->GetGameLayoutWidgetClass();
			RETURN_ON_INVALID(LayoutClass);
			auto* GameLayout = CreateWidget<UUI_GameLayout>(PlayerController, LayoutClass);
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

void UGameUIManagerSubsystem::SetGameUIPolicy(UGameUIPolicy* NewPolicy)
{
	if (this->CurrentUIPolicy != NewPolicy)
	{
		this->CurrentUIPolicy = NewPolicy;
	}
}
