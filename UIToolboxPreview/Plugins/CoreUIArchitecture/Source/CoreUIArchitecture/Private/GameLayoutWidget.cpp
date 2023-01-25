#include "GameLayoutWidget.h"

#include "CoreUILogs.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

UCommonActivatableWidgetContainerBase* UGameLayoutWidget::GetLayerWidget(FGameplayTag LayerName) const
{
	return this->Layers.FindRef(LayerName);
}

void UGameLayoutWidget::PopWidgetFromLayer(UCommonActivatableWidget* WidgetToRemove)
{
	if (WidgetToRemove == nullptr)
	{
		return;
	}
	for (const auto KVPair : this->Layers)
	{
		KVPair.Value->RemoveWidget(*WidgetToRemove);
	}
}

void UGameLayoutWidget::RegisterLayer(FGameplayTag LayerTag, UCommonActivatableWidgetContainerBase* LayerWidget)
{
	if (IsDesignTime())
	{
		return;
	}
	if (IsValid(LayerWidget) == false)
	{
		CORE_UI_ERROR("Trying to register NULL widget as a layer");
		return;
	}
	if (this->Layers.Contains(LayerTag))
	{
		CORE_UI_WARNING("Registering again widget with tag: %s", *LayerTag.ToString());
	}
	this->Layers.Add(LayerTag, LayerWidget);
}