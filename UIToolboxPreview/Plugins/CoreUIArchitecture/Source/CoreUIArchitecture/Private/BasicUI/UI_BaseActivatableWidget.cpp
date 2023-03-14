#include "CoreUIArchitecture/Public/BasicUI/UI_BaseActivatableWidget.h"

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
