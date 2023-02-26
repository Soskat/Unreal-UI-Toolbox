#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExampleTriggerBase.generated.h"

class UCommonActivatableWidget;
class AExamplePlayerController;

UCLASS(Abstract)
class UITOOLBOXPREVIEW_API AExampleTriggerBase : public AActor
{
	GENERATED_BODY()

public:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	UFUNCTION(BlueprintCallable, Category = Examples)
	void ExecuteExample();

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnExecuteExample();

	UPROPERTY(EditAnywhere, Category = Examples)
	TSubclassOf<UCommonActivatableWidget> InteractionPromptWidget = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
	AExamplePlayerController* CachedPlayerController = nullptr;
	
private:
	UPROPERTY(Transient)
	UCommonActivatableWidget* InteractionPrompt = nullptr;
};
