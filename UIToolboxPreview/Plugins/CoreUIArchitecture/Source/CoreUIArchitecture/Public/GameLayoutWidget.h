#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "GameplayTagContainer.h"
#include "GameLayoutWidget.generated.h"

class UCommonActivatableWidget;
class UCommonActivatableWidgetContainerBase;

UCLASS(Abstract, meta = (DisableNativeTick))
class COREUIARCHITECTURE_API UGameLayoutWidget : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	UCommonActivatableWidgetContainerBase* GetLayerWidget(FGameplayTag LayerName) const;

	template <typename ActivatableWidgetT = UCommonActivatableWidget>
	ActivatableWidgetT* PushWidgetToLayerStack(FGameplayTag LayerName, UClass* ActivatableWidgetClass)
	{
		return PushWidgetToLayerStack<ActivatableWidgetT>(LayerName,
			ActivatableWidgetClass,
			[](ActivatableWidgetT&)
			{
			});
	}

	template <typename ActivatableWidgetT = UCommonActivatableWidget>
	ActivatableWidgetT* PushWidgetToLayerStack(FGameplayTag LayerName,
		UClass* ActivatableWidgetClass,
		TFunctionRef<void(ActivatableWidgetT&)> InitInstanceFunc)
	{
		static_assert(TIsDerivedFrom<ActivatableWidgetT, UCommonActivatableWidget>::IsDerived, "Only CommonActivatableWidgets can be used here");

		if (UCommonActivatableWidgetContainerBase* Layer = GetLayerWidget(LayerName))
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
	TMap<FGameplayTag, UCommonActivatableWidgetContainerBase*> Layers = {};
};
