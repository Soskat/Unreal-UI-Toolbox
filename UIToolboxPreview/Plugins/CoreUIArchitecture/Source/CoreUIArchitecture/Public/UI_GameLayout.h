#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "GameplayTagContainer.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "UI_GameLayout.generated.h"

class UCommonActivatableWidget;

/**
 * This widget class represents how to layout, push and display all layers of the UI for a single player.
 * Each local player will receive their own game layout widget.
 */
UCLASS(Abstract, meta = (DisableNativeTick))
class COREUIARCHITECTURE_API UUI_GameLayout : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	TObjectPtr<UCommonActivatableWidgetContainerBase> GetLayerWidget(FGameplayTag LayerName) const;

	template <typename ActivatableWidgetT = UCommonActivatableWidget>
	ActivatableWidgetT* PushWidgetToLayerStack(FGameplayTag LayerName, TObjectPtr<UClass> ActivatableWidgetClass)
	{
		return PushWidgetToLayerStack<ActivatableWidgetT>(LayerName,
			ActivatableWidgetClass,
			[](ActivatableWidgetT&)
			{
			});
	}

	template <typename ActivatableWidgetT = UCommonActivatableWidget>
	ActivatableWidgetT* PushWidgetToLayerStack(FGameplayTag LayerName,
		TObjectPtr<UClass> ActivatableWidgetClass,
		TFunctionRef<void(ActivatableWidgetT&)> InitInstanceFunc)
	{
		static_assert(TIsDerivedFrom<ActivatableWidgetT, UCommonActivatableWidget>::IsDerived, "Only CommonActivatableWidgets can be used here");

		if (const auto Layer = GetLayerWidget(LayerName))
		{
			return Layer->AddWidget<ActivatableWidgetT>(ActivatableWidgetClass, InitInstanceFunc);
		}

		return nullptr;
	}

	void PopWidgetFromLayer(UCommonActivatableWidget* WidgetToRemove);

protected:
	UFUNCTION(BlueprintCallable, Category="Layer")
	void RegisterLayer(FGameplayTag LayerTag, UCommonActivatableWidgetContainerBase* LayerWidget);

private:
	UPROPERTY(Transient)
	TMap<FGameplayTag, TObjectPtr<UCommonActivatableWidgetContainerBase>> Layers = {};
};
