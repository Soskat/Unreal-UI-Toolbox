#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "ShowDialogAsyncAction.generated.h"

enum class EDialogResult : uint8;
class UGameDialogDescriptor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDialogResultMCDelegate, EDialogResult, Result);

/**
 * Allows easily triggering an async dialog in blueprints that you can then wait on the result.
 */
UCLASS()
class COREUIARCHITECTURE_API UShowDialogAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, meta = (BlueprintInternalUseOnly = "true", WorldContext = "InWorldContextObject"))
	static UShowDialogAsyncAction* ShowErrorOk(
		UObject* InWorldContextObject,
		FText Title,
		FText Message
		);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, meta = (BlueprintInternalUseOnly = "true", WorldContext = "InWorldContextObject"))
	static UShowDialogAsyncAction* ShowConfirmationOk(
		UObject* InWorldContextObject,
		FText Title,
		FText Message
		);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, meta = (BlueprintInternalUseOnly = "true", WorldContext = "InWorldContextObject"))
	static UShowDialogAsyncAction* ShowConfirmationOkCancel(
		UObject* InWorldContextObject,
		FText Title,
		FText Message
		);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, meta = (BlueprintInternalUseOnly = "true", WorldContext = "InWorldContextObject"))
	static UShowDialogAsyncAction* ShowConfirmationYesNo(
		UObject* InWorldContextObject,
		FText Title,
		FText Message
		);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, meta = (BlueprintInternalUseOnly = "true", WorldContext = "InWorldContextObject"))
	static UShowDialogAsyncAction* ShowConfirmationCustom(
		UObject* InWorldContextObject,
		UGameDialogDescriptor* Descriptor
		);

	virtual void Activate() override;

public:
	UPROPERTY(BlueprintAssignable)
	FDialogResultMCDelegate OnResult;

private:
	TObjectPtr<ULocalPlayer> TryGetLocalPlayer();
	void HandleDialogResult(EDialogResult ConfirmationResult);

	UPROPERTY(Transient)
	bool bIsConfirmation = true;

	UPROPERTY(Transient)
	TObjectPtr<UObject> WorldContextObject = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<ULocalPlayer> TargetLocalPlayer = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<UGameDialogDescriptor> Descriptor = nullptr;
};
