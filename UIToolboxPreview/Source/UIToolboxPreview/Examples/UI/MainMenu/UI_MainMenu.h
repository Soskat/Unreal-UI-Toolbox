#pragma once

#include "CoreMinimal.h"
#include "CoreUIArchitecture/Public/BasicUI/UI_BaseActivatableWidget.h"
#include "UI_MainMenu.generated.h"

enum class EDialogResult : uint8;

UCLASS()
class UITOOLBOXPREVIEW_API UUI_MainMenu : public UUI_BaseActivatableWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category = MainMenu)
	void ShowConfirmationDialogExample() const;
	
	UFUNCTION(BlueprintCallable, Category = MainMenu)
	void ShowErrorDialogExample() const;
	
	UFUNCTION(BlueprintCallable, Category = MainMenu)
	void ShowComplexDialogExample() const;

	UFUNCTION(BlueprintCallable, Category = MainMenu)
	void ShowConfirmationForOpenGameplayLevel();
	UFUNCTION(BlueprintCallable, Category = MainMenu)
	void ShowConfirmationForQuitGame();

private:
	UFUNCTION()
	void HandleOpenGameplayLevelConfirmationResult(EDialogResult Result);

	UFUNCTION()
	void HandleQuitGameConfirmationResult(EDialogResult Result);

	UPROPERTY(EditAnywhere, Category = MainMenu)
	TSubclassOf<UCommonActivatableWidget> EditNumberExampleClass = nullptr;

	UPROPERTY(EditAnywhere, Category = MainMenu)
	FName GameplayLevelName = {};
};
