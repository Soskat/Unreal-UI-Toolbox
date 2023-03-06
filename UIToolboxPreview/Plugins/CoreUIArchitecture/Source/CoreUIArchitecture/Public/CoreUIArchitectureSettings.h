#pragma once

#include "CoreMinimal.h"
#include "Messaging/MessagingPolicy.h"

#include "CoreUIArchitectureSettings.generated.h"

USTRUCT(BlueprintType)
struct FUIPolicyRecord
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories = "UI.Policy"))
	FGameplayTag UIPolicyTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftClassPtr<UMessagingPolicy> UIPolicyClass;
};

UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Core UI Architecture"))
class COREUIARCHITECTURE_API UCoreUIArchitectureSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UCoreUIArchitectureSettings()
	{
	}
	
	UFUNCTION(BlueprintCallable, Category = "Game Layout")
	TSubclassOf<UUI_GameLayout> GetGameLayoutWidgetClass() const;
	
	UPROPERTY(Config, EditAnywhere, Category = "Game Layout")
	TSoftClassPtr<UUI_GameLayout> GameLayoutWidgetClass = nullptr;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Messaging UI Policy")
	TArray<FUIPolicyRecord> AvailableUIPolicies = {};
};
