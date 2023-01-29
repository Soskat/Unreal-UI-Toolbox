#pragma once

#include "CoreMinimal.h"
#include "BasePlayerController.h"
#include "ExampleTriggerBase.h"

#include "ExamplePlayerController.generated.h"

UCLASS(Abstract)
class UITOOLBOXPREVIEW_API AExamplePlayerController : public ABasePlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	AExampleTriggerBase* GetExampleTrigger() const
	{
		return this->ActiveExample;
	}

	UFUNCTION(BlueprintCallable)
	void SetExampleTrigger(AExampleTriggerBase* ExampleTrigger)
	{
		this->ActiveExample = ExampleTrigger;
	}

private:
	UPROPERTY(Transient)
	AExampleTriggerBase* ActiveExample = nullptr;
};
