#include "CoreUIUtils.h"

#include "CommonInputSubsystem.h"
#include "GameLayoutWidget.h"
#include "LayeredHUD.h"
#include "Kismet/GameplayStatics.h"

int32 UCoreUIUtils::InputSuspensions = 0;

UGameLayoutWidget* UCoreUIUtils::GetGameLayoutWidget(const UObject* WorldContextObject)
{
	if (IsValid(WorldContextObject))
	{
		if (const auto* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
		{
			if (const auto* LayeredHUD = Cast<ALayeredHUD>(PlayerController->GetHUD()))
			{
				return LayeredHUD->GetGameLayoutWidget();
			}
		}
	}
	return nullptr;
}

UCommonActivatableWidget* UCoreUIUtils::PushContentToLayer(const UObject* WorldContextObject,
	FGameplayTag LayerName,
	TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
	if (auto* GameLayoutWidget = GetGameLayoutWidget(WorldContextObject))
	{
		return GameLayoutWidget->PushWidgetToLayerStack(LayerName, WidgetClass);
	}
	return nullptr;
}

void UCoreUIUtils::PopContentFromLayer(UCommonActivatableWidget* ActivatableWidget)
{
	if (IsValid(ActivatableWidget) == false)
	{
		return;
	}
	if (auto* GameLayoutWidget = GetGameLayoutWidget(ActivatableWidget->GetOwningPlayer()))
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
