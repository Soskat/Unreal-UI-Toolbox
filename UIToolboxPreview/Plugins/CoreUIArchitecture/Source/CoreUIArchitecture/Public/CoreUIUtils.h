#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CoreUIUtils.generated.h"

class UUI_GameLayout;

/**
 * This class contains a set of utility functions for adding and removing content from game layout widget
 * for specific player and for suspending and restoring UI input.
 */
UCLASS()
class COREUIARCHITECTURE_API UCoreUIUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, BlueprintCosmetic, Category = "Core UI Utils")
	static ULocalPlayer* GetLocalPlayerFromController(APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Core UI Utils", meta = (WorldContext = "WidgetContextObject"))
	static UUI_GameLayout* GetGameLayoutWidgetForPlayer(ULocalPlayer* LocalPlayer);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Core UI Utils")
	static UCommonActivatableWidget* PushContentToLayerForPlayer(
		ULocalPlayer* LocalPlayer,
		UPARAM(meta = (Categories = "UI.Layers")) FGameplayTag LayerName,
		UPARAM(meta = (AllowAbstract = false)) TSubclassOf<UCommonActivatableWidget> WidgetClass
	);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Core UI Utils")
	static void PopContentFromLayerForPlayer(ULocalPlayer* LocalPlayer, UCommonActivatableWidget* ActivatableWidget);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Core UI Utils")
	static FName SuspendInputForPlayer(APlayerController* PlayerController, FName SuspendReason);

	static FName SuspendInputForPlayer(const ULocalPlayer* LocalPlayer, FName SuspendReason);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Core UI Utils")
	static void ResumeInputForPlayer(APlayerController* PlayerController, FName SuspendToken);

	static void ResumeInputForPlayer(const ULocalPlayer* LocalPlayer, FName SuspendToken);

private:
	static int32 InputSuspensions;
};
