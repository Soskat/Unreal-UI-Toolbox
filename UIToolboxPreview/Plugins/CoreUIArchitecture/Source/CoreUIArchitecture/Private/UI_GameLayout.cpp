#include "UI_GameLayout.h"

#include "CoreUILogs.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

TObjectPtr<UCommonActivatableWidgetContainerBase> UUI_GameLayout::GetLayerWidget(FGameplayTag LayerName) const
{
	return this->Layers.FindRef(LayerName);
}

void UUI_GameLayout::PopWidgetFromLayer(UCommonActivatableWidget* WidgetToRemove)
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

void UUI_GameLayout::RegisterLayer(FGameplayTag LayerTag, UCommonActivatableWidgetContainerBase* LayerWidget)
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