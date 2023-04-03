#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "UI_BaseActivatableWidget.generated.h"

UENUM(BlueprintType)
enum class ECommonWidgetInputMode : uint8
{
	Default,
	GameAndMenu,
	Game,
	Menu
};

/**
 * Extended version of an activatable widget, that additionally drives the desired input configuration when activated.
 */
UCLASS(Abstract, Blueprintable)
class COREUIARCHITECTURE_API UUI_BaseActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	//~UCommonActivatableWidget interface
	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;
	//~End of UCommonActivatableWidget interface

protected:
	//~UUserWidget interface
	virtual void NativeConstruct() override;
	//~End of UUserWidget interface
	
	/** The desired input mode to use while this UI is activated, for example do you want key presses to still reach the game/player controller? */
	UPROPERTY(EditDefaultsOnly, Category = Input)
	ECommonWidgetInputMode InputConfig = ECommonWidgetInputMode::Default;

	/** The desired mouse behavior when the game gets input. */
	UPROPERTY(EditDefaultsOnly, Category = Input)
	EMouseCaptureMode GameMouseCaptureMode = EMouseCaptureMode::CapturePermanently;

	/** Should we force applying associated input config when this widget is constructed? */
	UPROPERTY(EditDefaultsOnly, Category = Input)
	bool bForceInputChangeUponConstruction = false;
};
