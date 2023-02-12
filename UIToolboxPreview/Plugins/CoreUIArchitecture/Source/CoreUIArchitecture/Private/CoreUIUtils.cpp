#include "CoreUIUtils.h"

#include "CommonInputSubsystem.h"
#include "GameUIManagerSubsystem.h"
#include "UI_GameLayout.h"
#include "Kismet/GameplayStatics.h"

int32 UCoreUIUtils::InputSuspensions = 0;

ULocalPlayer* UCoreUIUtils::GetLocalPlayerFromController(APlayerController* PlayerController)
{
	if (IsValid(PlayerController))
	{
		return Cast<ULocalPlayer>(PlayerController->Player);
	}
	return nullptr;
}

UUI_GameLayout* UCoreUIUtils::GetGameLayoutWidgetForPlayer(ULocalPlayer* LocalPlayer)
{
	if (IsValid(LocalPlayer) == false)
	{
		return nullptr;
	}
	const auto* GameInstance = UGameplayStatics::GetGameInstance(LocalPlayer);
	if (IsValid(GameInstance) == false)
	{
		return nullptr;
	}
	UGameUIManagerSubsystem* GameUIManager = GameInstance->GetSubsystem<UGameUIManagerSubsystem>();
	if (IsValid(GameUIManager) == false)
	{
		return nullptr;
	}
	return GameUIManager->GetGameLayoutForPlayer(LocalPlayer);
}

UCommonActivatableWidget* UCoreUIUtils::PushContentToLayerForPlayer(ULocalPlayer* LocalPlayer,
                                                                    FGameplayTag LayerName,
                                                                    TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
	if (auto* GameLayoutWidget = GetGameLayoutWidgetForPlayer(LocalPlayer))
	{
		return GameLayoutWidget->PushWidgetToLayerStack(LayerName, WidgetClass);
	}
	return nullptr;
}

void UCoreUIUtils::PopContentFromLayerForPlayer(ULocalPlayer* LocalPlayer, UCommonActivatableWidget* ActivatableWidget)
{
	if (IsValid(ActivatableWidget) == false)
	{
		return;
	}
	if (auto* GameLayoutWidget = GetGameLayoutWidgetForPlayer(LocalPlayer))
	{
		GameLayoutWidget->PopWidgetFromLayer(ActivatableWidget);
	}
}

FName UCoreUIUtils::SuspendInputForPlayer(APlayerController* PlayerController, FName SuspendReason)
{
	return SuspendInputForPlayer(PlayerController ? PlayerController->GetLocalPlayer() : nullptr, SuspendReason);
}

FName UCoreUIUtils::SuspendInputForPlayer(const ULocalPlayer* LocalPlayer, const FName SuspendReason)
{
	if (auto* CommonInputSubsystem = UCommonInputSubsystem::Get(LocalPlayer))
	{
		InputSuspensions++;
		FName SuspendToken = SuspendReason;
		SuspendToken.SetNumber(InputSuspensions);

		CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::MouseAndKeyboard, SuspendToken, true);
		CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::Gamepad, SuspendToken, true);
		CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::Touch, SuspendToken, true);

		return SuspendToken;
	}
	return NAME_None;
}

void UCoreUIUtils::ResumeInputForPlayer(APlayerController* PlayerController, const FName SuspendToken)
{
	ResumeInputForPlayer(PlayerController ? PlayerController->GetLocalPlayer() : nullptr, SuspendToken);
}

void UCoreUIUtils::ResumeInputForPlayer(const ULocalPlayer* LocalPlayer, const FName SuspendToken)
{
	if (SuspendToken == NAME_None)
	{
		return;
	}
	if (auto* CommonInputSubsystem = UCommonInputSubsystem::Get(LocalPlayer))
	{
		CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::MouseAndKeyboard, SuspendToken, false);
		CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::Gamepad, SuspendToken, false);
		CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::Touch, SuspendToken, false);
	}
}
