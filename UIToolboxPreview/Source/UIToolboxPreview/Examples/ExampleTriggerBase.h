#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExampleTriggerBase.generated.h"

class AExamplePlayerController;
class UUI_InformationPrompt;

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
	TSubclassOf<UUI_InformationPrompt> InteractionPromptWidget = nullptr;

	UPROPERTY(EditAnywhere, Category = Examples)
	FText InformationText = FText::AsCultureInvariant(TEXT("<information prompt text>"));
	
	UPROPERTY(BlueprintReadOnly)
	AExamplePlayerController* CachedPlayerController = nullptr;
	
private:
	UPROPERTY(Transient)
	UUI_InformationPrompt* InteractionPrompt = nullptr;
};
