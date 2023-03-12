#pragma once

#include "CoreMinimal.h"
#include "GameDialogDescriptor.h"
#include "GameplayTagContainer.h"
#include "Subsystems/LocalPlayerSubsystem.h"

#include "MessagingSubsystem.generated.h"

class UMessagingPolicy;
class UUI_BaseDialog;

/**
 * This subsystem is providing methods for displaying confirmation and error dialogs.
 */
UCLASS()
class COREUIARCHITECTURE_API UMessagingSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	UFUNCTION(BlueprintCallable, Category = "Messaging")
	void SetMessagingPolicy(UMessagingPolicy* NewPolicy);
	
	UFUNCTION(BlueprintCallable, Category = "Messaging")
	void SetMessagingPolicyFromTag(UPARAM(meta = (Categories = "UI.Policy")) FGameplayTag PolicyTag);
	
	UFUNCTION(BlueprintCallable, Category = "Messaging")
	void SetDefaultMessagingPolicy();
	
	TObjectPtr<UMessagingPolicy> GetCurrentMessagingPolicy() const
	{
		return this->CurrentPolicy;
	}
	
	void ShowConfirmation(TObjectPtr<UGameDialogDescriptor> DialogDescriptor, FDialogResultDelegate ResultCallback = FDialogResultDelegate());
	void ShowError(TObjectPtr<UGameDialogDescriptor> DialogDescriptor, FDialogResultDelegate ResultCallback = FDialogResultDelegate());

private:
	void ShowDialogInternal(TObjectPtr<UGameDialogDescriptor> DialogDescriptor, FDialogResultDelegate ResultCallback, TSubclassOf<UUI_BaseDialog> DialogClass);
	TSubclassOf<UUI_BaseDialog> GetConfirmationDialogClass() const;
	TSubclassOf<UUI_BaseDialog> GetErrorDialogClass() const;

	UPROPERTY()
	TObjectPtr<UMessagingPolicy> CurrentPolicy = nullptr;

	UPROPERTY()
	TMap<FGameplayTag, TSubclassOf<UMessagingPolicy>> AvailablePolicies = {};
};