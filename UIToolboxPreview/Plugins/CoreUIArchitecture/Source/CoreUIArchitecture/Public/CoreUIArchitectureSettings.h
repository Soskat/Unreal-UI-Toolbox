#pragma once

#include "CoreMinimal.h"
#include "GameUIPolicy.h"

#include "CoreUIArchitectureSettings.generated.h"

UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Core UI Architecture"))
class COREUIARCHITECTURE_API UCoreUIArchitectureSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UCoreUIArchitectureSettings()
	{
	}

	TSubclassOf<UGameUIPolicy> GetDefaultUIPolicyClass() const;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly)
	TSoftClassPtr<UGameUIPolicy> DefaultUIPolicyClass;
};
