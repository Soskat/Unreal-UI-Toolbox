#pragma once

#include "CoreMinimal.h"
#include "UI_GameLayout.h"
#include "GameUIPolicy.generated.h"

UCLASS(Abstract, Blueprintable, Within = GameUIManagerSubsystem)
class COREUIARCHITECTURE_API UGameUIPolicy : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Game UI Policy")
	TSubclassOf<UUI_GameLayout> GetGameLayoutWidgetClass() const;

private:
	UPROPERTY(EditAnywhere)
	TSoftClassPtr<UUI_GameLayout> GameLayoutWidgetClass = nullptr;
};
