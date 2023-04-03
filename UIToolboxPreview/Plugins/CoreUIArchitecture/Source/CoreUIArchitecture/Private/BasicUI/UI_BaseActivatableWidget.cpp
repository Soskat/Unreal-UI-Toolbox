#include "CoreUIArchitecture/Public/BasicUI/UI_BaseActivatableWidget.h"
#include "CoreUIArchitecture/Public/CoreUILogs.h"
#include "CommonUI/Public/Input/CommonUIActionRouterBase.h"

TOptional<FUIInputConfig> UUI_BaseActivatableWidget::GetDesiredInputConfig() const
{
	switch (this->InputConfig)
	{
		case ECommonWidgetInputMode::GameAndMenu:
			return FUIInputConfig(ECommonInputMode::All, GameMouseCaptureMode);
		case ECommonWidgetInputMode::Game:
			return FUIInputConfig(ECommonInputMode::Game, GameMouseCaptureMode);
		case ECommonWidgetInputMode::Menu:
			return FUIInputConfig(ECommonInputMode::Menu, EMouseCaptureMode::NoCapture);
		case ECommonWidgetInputMode::Default:
		default:
			return TOptional<FUIInputConfig>();
	}
}

void  UUI_BaseActivatableWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (this->bForceInputChangeUponConstruction)
	{
		UCommonUIActionRouterBase* ActionRouter = UCommonUIActionRouterBase::Get(*this);
		if (IsValid(ActionRouter))
		{
			TOptional<FUIInputConfig> DesiredConfig = GetDesiredInputConfig();
			if (DesiredConfig.IsSet())
			{
				CORE_UI_LOG("%s::NativeConstruct() | Force new Input config: %s", *this->GetName(), *UEnum::GetValueAsName(this->InputConfig).ToString());
				ActionRouter->SetActiveUIInputConfig(DesiredConfig.GetValue());
			}
		}
	}
}